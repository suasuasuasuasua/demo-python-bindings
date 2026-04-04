#!/usr/bin/env python3
"""
dev.py — helper script for common development tasks.

Subcommands:
  build    Configure and build the project with CMake
  test     Run C++ (ctest) and/or Python tests
  clean    Remove build artifacts
  format   Run clang-format over C++ sources (and optionally black over Python)

Run `python dev.py <subcommand> --help` for per-command options.
"""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

ROOT = Path(__file__).resolve().parent
SRC_CPP = ROOT / "src"
SRC_PY_TESTS = ROOT / "tests" / "python"
CPP_EXTENSIONS = ("*.cpp", "*.h")

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def run(cmd: list, **kwargs):
    """Print and execute a command, exit on non-zero return code."""
    print("+", " ".join(str(c) for c in cmd))
    result = subprocess.run(cmd, **kwargs)
    if result.returncode != 0:
        sys.exit(result.returncode)


def require(tool: str, hint: str = ""):
    """Exit with a friendly message if a tool is not on PATH."""
    if shutil.which(tool) is None:
        msg = f"error: '{tool}' not found on PATH."
        if hint:
            msg += f" {hint}"
        print(msg, file=sys.stderr)
        sys.exit(1)


# ---------------------------------------------------------------------------
# Subcommands
# ---------------------------------------------------------------------------


def cmd_build(args):
    build_dir = ROOT / args.build_dir

    cmake_args = [
        "cmake",
        "-B",
        build_dir,
        f"-DCMAKE_BUILD_TYPE={args.build_type}",
        f"-DBUILD_PYTHON_BINDINGS={'ON' if args.python_bindings else 'OFF'}",
        f"-DBUILD_TESTING={'ON' if args.tests else 'OFF'}",
    ]

    if args.toolchain:
        cmake_args += [f"-DCMAKE_TOOLCHAIN_FILE={args.toolchain}"]
    if args.emulator:
        cmake_args += [f"-DCMAKE_CROSSCOMPILING_EMULATOR={args.emulator}"]
    if args.extra_cmake:
        cmake_args += args.extra_cmake

    require("cmake", "Install CMake 3.17+ from https://cmake.org/download/")
    run(cmake_args)
    run(["cmake", "--build", build_dir, "--config", args.build_type, "--parallel"])


def cmd_test(args):
    build_dir = ROOT / args.build_dir

    if not args.python_only:
        require("ctest", "ctest ships with CMake — make sure CMake is installed.")
        if not (build_dir / "CTestTestfile.cmake").exists():
            print(
                f"error: no CTest files found in '{build_dir}'.\n"
                "Run `python dev.py build --tests` first.",
                file=sys.stderr,
            )
            sys.exit(1)

        ctest_args = [
            "ctest",
            "--test-dir",
            build_dir,
            "-C",
            args.build_type,
            "--output-on-failure",
        ]
        if args.verbose:
            ctest_args.append("-V")

        env_extra = {}
        if args.winedebug:
            import os

            env_extra = {**os.environ, "WINEDEBUG": "-all"}

        run(ctest_args, env=env_extra if env_extra else None)

    if not args.cpp_only:
        run([sys.executable, "-m", "unittest", "discover", "-s", str(SRC_PY_TESTS), "-v"])


def cmd_clean(args):
    targets = [ROOT / d for d in args.dirs]
    for target in targets:
        if target.exists():
            print(f"Removing {target}")
            shutil.rmtree(target)
        else:
            print(f"Nothing to clean: {target}")

    # Also remove Python build artifacts
    if not args.keep_py:
        for pattern in ("**/__pycache__", "**/*.egg-info", "dist", "*.egg-info"):
            for path in ROOT.glob(pattern):
                if path.exists():
                    print(f"Removing {path}")
                    shutil.rmtree(path) if path.is_dir() else path.unlink()


def cmd_format(args):
    # --- C++ formatting with clang-format ---
    if not args.python_only:
        require(
            "clang-format",
            "Install via your package manager or VS Build Tools (Windows).",
        )
        cpp_files = []
        for ext in CPP_EXTENSIONS:
            cpp_files.extend(SRC_CPP.rglob(ext))
            cpp_files.extend((ROOT / "tests" / "cpp").rglob(ext))

        if not cpp_files:
            print("No C++ files found.")
        else:
            clang_args = ["clang-format"]
            if not args.check:
                clang_args.append("-i")
            else:
                clang_args += ["--dry-run", "--Werror"]
            run(clang_args + [str(f) for f in sorted(cpp_files)])

    # --- Python formatting with isort + black ---
    if not args.cpp_only:
        py_targets = [str(ROOT / "tests" / "python"), str(ROOT / "dev.py")]

        require("isort", "Install with: pip install isort")
        isort_args = ["isort"]
        if args.check:
            isort_args.append("--check")
        run(isort_args + py_targets)

        require("black", "Install with: pip install black")
        black_args = ["black"]
        if args.check:
            black_args.append("--check")
        run(black_args + py_targets)


# ---------------------------------------------------------------------------
# Argument parsing
# ---------------------------------------------------------------------------


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="dev.py",
        description="Development helper for myMathLib.",
    )
    sub = parser.add_subparsers(dest="subcommand", required=True)

    # ── build ───────────────────────────────────────────────────────────────
    p_build = sub.add_parser("build", help="Configure and build with CMake")
    p_build.add_argument(
        "-d",
        "--build-dir",
        default="build",
        metavar="DIR",
        help="CMake build directory (default: build)",
    )
    p_build.add_argument(
        "-t",
        "--build-type",
        default="Release",
        choices=["Release", "Debug", "RelWithDebInfo", "MinSizeRel"],
        help="CMake build type (default: Release)",
    )
    p_build.add_argument(
        "--python-bindings",
        action="store_true",
        default=True,
        help="Build Python bindings via pybind11 (default: on)",
    )
    p_build.add_argument(
        "--no-python-bindings",
        dest="python_bindings",
        action="store_false",
        help="Disable Python bindings",
    )
    p_build.add_argument(
        "--tests",
        action="store_true",
        default=False,
        help="Enable C++ GoogleTest targets (default: off)",
    )
    p_build.add_argument(
        "--toolchain",
        metavar="FILE",
        help="Path to a CMake toolchain file (e.g. for MinGW cross-compile)",
    )
    p_build.add_argument(
        "--emulator",
        metavar="BIN",
        help="Cross-compiling emulator passed to CMAKE_CROSSCOMPILING_EMULATOR "
        "(e.g. path to wine for MinGW builds)",
    )
    p_build.set_defaults(func=cmd_build, extra_cmake=[])

    # ── test ────────────────────────────────────────────────────────────────
    p_test = sub.add_parser("test", help="Run C++ (ctest) and/or Python tests")
    p_test.add_argument(
        "-d",
        "--build-dir",
        default="build",
        metavar="DIR",
        help="CMake build directory to run ctest from (default: build)",
    )
    p_test.add_argument(
        "-t",
        "--build-type",
        default="Release",
        choices=["Release", "Debug", "RelWithDebInfo", "MinSizeRel"],
        help="Build configuration passed to ctest -C (default: Release)",
    )
    p_test.add_argument(
        "--cpp-only",
        action="store_true",
        help="Run C++ tests only (skip Python tests)",
    )
    p_test.add_argument(
        "--python-only",
        action="store_true",
        help="Run Python tests only (skip ctest)",
    )
    p_test.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Pass -V to ctest for verbose output",
    )
    p_test.add_argument(
        "--winedebug",
        action="store_true",
        help="Set WINEDEBUG=-all to suppress Wine noise during cross-compile tests",
    )
    p_test.set_defaults(func=cmd_test)

    # ── clean ───────────────────────────────────────────────────────────────
    p_clean = sub.add_parser("clean", help="Remove build artifacts")
    p_clean.add_argument(
        "--dirs",
        nargs="+",
        default=["build"],
        metavar="DIR",
        help="Build directories to remove (default: build)",
    )
    p_clean.add_argument(
        "--keep-py",
        action="store_true",
        help="Do not remove Python __pycache__ / .egg-info / dist artifacts",
    )
    p_clean.set_defaults(func=cmd_clean)

    # ── format ──────────────────────────────────────────────────────────────
    p_fmt = sub.add_parser(
        "format",
        help="Format C++ sources with clang-format and Python files with black",
    )
    p_fmt.add_argument(
        "--check",
        action="store_true",
        help="Validate formatting without modifying files (exits non-zero if "
        "any file would change)",
    )
    p_fmt.add_argument(
        "--cpp-only",
        action="store_true",
        help="Format C++ files only (skip black)",
    )
    p_fmt.add_argument(
        "--python-only",
        action="store_true",
        help="Format Python files only (skip clang-format)",
    )
    p_fmt.set_defaults(func=cmd_format)

    return parser


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    # argparse treats '--' as a special end-of-options sentinel and cannot
    # parse it as a named argument.  Split sys.argv manually so that
    # everything after the first '--' is collected as extra cmake arguments
    # and is never seen by argparse.
    argv = sys.argv[1:]
    extra_cmake: list[str] = []
    if "--" in argv:
        idx = argv.index("--")
        extra_cmake = argv[idx + 1 :]
        argv = argv[:idx]

    parser = build_parser()
    args = parser.parse_args(argv)
    # Attach the pass-through cmake args (only meaningful for 'build').
    if hasattr(args, "extra_cmake"):
        args.extra_cmake = extra_cmake
    args.func(args)

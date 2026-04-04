import pytest
import myMathLib


def test_add():
    assert myMathLib.add(3, 4) == pytest.approx(7.0)
    assert myMathLib.add(-1, 1) == pytest.approx(0.0)
    assert myMathLib.add(0, 0) == pytest.approx(0.0)
    assert myMathLib.add(-5, -3) == pytest.approx(-8.0)


def test_subtract():
    assert myMathLib.subtract(10, 3) == pytest.approx(7.0)
    assert myMathLib.subtract(0, 5) == pytest.approx(-5.0)


def test_multiply():
    assert myMathLib.multiply(6, 7) == pytest.approx(42.0)
    assert myMathLib.multiply(-2, 3) == pytest.approx(-6.0)
    assert myMathLib.multiply(0, 100) == pytest.approx(0.0)


def test_divide():
    assert myMathLib.divide(15, 3) == pytest.approx(5.0)
    assert myMathLib.divide(1, 4) == pytest.approx(0.25)


def test_divide_by_zero():
    with pytest.raises(ValueError, match="Division by zero"):
        myMathLib.divide(1, 0)


def test_power():
    assert myMathLib.power(2, 8) == pytest.approx(256.0)
    assert myMathLib.power(3, 0) == pytest.approx(1.0)
    assert myMathLib.power(5, -1) == pytest.approx(0.2)


def test_module_docstring():
    assert myMathLib.__doc__ is not None
    assert len(myMathLib.__doc__) > 0

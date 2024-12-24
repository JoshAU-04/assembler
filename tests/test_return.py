import pytest
from subprocess import Popen, PIPE


@pytest.fixture()
def path():
    return "/home/t_doctor/Projects/assembler/tests/data/test_return.rl"


@pytest.fixture()
def process(path):
    return Popen(["./program", path], stdout=PIPE)


def test_return_msg(process):
    out, _ = process.communicate()
    assert out.decode() == "Found return value.\n"

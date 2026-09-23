"""O mesmo contrato local e remoto; as etapas 01 e 02 são cumulativas."""
from pathlib import Path
import os
import subprocess
import sys


def main():
    etapa = sys.argv[1] if len(sys.argv) > 1 else ""
    if etapa not in ("00", "01", "02"):
        raise SystemExit("Use make test ETAPA=00|01|02 (00 verifica somente a base fornecida)")
    Path("build").mkdir(exist_ok=True)
    compiler = subprocess.run([
        "g++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
        "-Iinclude", "tests/contrato.cpp", "-o", "build/contrato",
    ])
    env = {**os.environ, "PYTHONPATH": "src", "PYTHONDONTWRITEBYTECODE": "1"}
    codes = [compiler.returncode]
    if compiler.returncode == 0:
        codes.append(subprocess.run(["./build/contrato", etapa]).returncode)
    codes.append(subprocess.run(["python3", "tests/contrato.py", etapa], env=env).returncode)
    if any(codes):
        raise SystemExit(1)
    print(f"OK etapa {etapa} cumulativa (C++ e Python)")


if __name__ == "__main__":
    main()

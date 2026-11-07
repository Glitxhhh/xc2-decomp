#!/usr/bin/env python3
"""Convert the verified README progress snapshot to decompilati.onl JSON.

Run `check --readme` locally before committing updated progress; the pre-commit hook also refreshes
progress/areas.json, the per-zone byte totals added to the report as areas. This script does not compile sources
or require the original game binary.
"""
import argparse
import json
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parent.parent
NUMBER = r"(?:0|[1-9][0-9]*|[1-9][0-9]{0,2}(?:,[0-9]{3})+)"
PROGRESS = re.compile(
    rf"\s*({NUMBER}) / ({NUMBER}) functions \([0-9]+\.[0-9]+%\), "
    rf"({NUMBER}) / ({NUMBER}) bytes of code \([0-9]+\.[0-9]+%\)\s*"
)

AREAS = ROOT / "progress" / "areas.json"


def read_progress(text):
    blocks = re.findall(r"<!-- progress -->(.*?)<!-- /progress -->", text, re.S)
    if len(blocks) != 1:
        raise ValueError("expected exactly one README progress block")
    match = PROGRESS.fullmatch(blocks[0])
    if not match:
        raise ValueError("unrecognized README progress format; run check --readme")
    functions, total_functions, code, total_code = (
        int(value.replace(",", "")) for value in match.groups()
    )
    if not 0 <= functions <= total_functions or total_functions == 0:
        raise ValueError("invalid function counts")
    if not 0 <= code <= total_code or total_code == 0:
        raise ValueError("invalid code byte counts")
    return {
        "unit": "bytes",
        "version": "1.0.0",
        "code": {"total": total_code, "matching": code, "non_matching": 0},
        "functions": {"total": total_functions, "matching": functions},
    }


def read_areas(path, total_code):
    try:
        text = path.read_text()
    except FileNotFoundError:
        return None
    areas = json.loads(text)
    if not isinstance(areas, list) or not areas:
        raise ValueError(f"{path.name} must be a non-empty list of areas")
    for key in ("total", "matching", "non_matching"):
        if sum(area["code"][key] for area in areas) != total_code[key]:
            raise ValueError(f"{path.name} does not add up to the README code {key}; run the pre-commit hook")
    return areas


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--readme", type=Path, default=ROOT / "README.md")
    parser.add_argument("--areas", type=Path, default=AREAS)
    args = parser.parse_args()
    try:
        report = read_progress(args.readme.read_text())
        areas = read_areas(args.areas, report["code"])
    except (OSError, ValueError, KeyError, TypeError) as error:
        parser.exit(1, f"progress: {error}\n")
    if areas:
        report["areas"] = areas
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()

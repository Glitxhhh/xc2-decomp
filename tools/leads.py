#!/usr/bin/env python3
"""Rank what blocks the unmatched functions: the categories of work/blockers.json by the functions and the bytes they
hold back, overall and per zone. Needs work/blockers.json and work/status.json (blockers.py, status.py).

Usage:
  leads.py                  kinds of blocker overall, then the best leads overall and per zone
  leads.py --zone gf        only that zone (a source directory name: gf, battle, framework...)
  leads.py --top 20         leads shown per table (default 10)
  leads.py --by-functions   rank by functions instead of bytes
  leads.py --include-other  also rank the unspecific `other` records, one line per detail
  leads.py --json           the same numbers as JSON

A lead is a full category (shared-type:GfPropertyField, container:FixedVector::resize, registers...). A function
with several blockers counts under each of them. "alone" counts the functions that have no other blocker: solving
the lead is the only thing between them and a match, so it is the number of functions it can free at most.
Functions that match now are ignored: run `blockers.py retire` to drop their records.
"""
import argparse
import collections
import json
import sys

import blockers


def rows(zone=None):
    """The blockers of the functions not matched yet, the categories of each function and the function sizes."""
    by_name = blockers.status_by_name(blockers.load_status())
    unmatched = [b for b in blockers.load_blockers()["blockers"]
                 if by_name.get(b["mangled"], {"state": "todo"})["state"] != "match"]
    if zone:
        unmatched = [b for b in unmatched if b["zone"] == zone]
    kinds_of = collections.defaultdict(set)
    for b in unmatched:
        kinds_of[b["mangled"]].add(b["category"])
    sizes = {b["mangled"]: by_name.get(b["mangled"], {}).get("size", 0) for b in unmatched}
    return unmatched, kinds_of, sizes


def rank(unmatched, kinds_of, sizes, key, ignore_other=False):
    """{key: (functions, bytes, alone)}: alone counts the functions whose only blocker (an `other` note aside, when
    ignore_other) falls under that key."""
    groups = collections.defaultdict(set)
    for b in unmatched:
        groups[key({"category": b["category"]})].add(b["mangled"])
    out = {}
    for name, functions in groups.items():
        alone = {f for f in functions
                 if all(key({"category": c}) == name for c in kinds_of[f] if not (ignore_other and c == "other"))}
        out[name] = (len(functions), sum(sizes[f] for f in functions), len(alone))
    return out


def kind_of(b):
    return b["category"].split(":")[0]


def lead_of(b):
    return b["category"]


def table(title, ranked, top, by_functions):
    index = 0 if by_functions else 1
    ordered = sorted(ranked.items(), key=lambda kv: (-kv[1][index], -kv[1][1 - index], kv[0]))[:top]
    print(title)
    print(f"  {'lead':<48}{'functions':>10}{'bytes':>10}{'alone':>7}")
    for name, (functions, size, alone) in ordered:
        print(f"  {name[:47]:<48}{functions:>10}{size:>10,}{alone:>7}")
    if not ordered:
        print("  (none)")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--zone")
    parser.add_argument("--top", type=int, default=10)
    parser.add_argument("--by-functions", action="store_true")
    parser.add_argument("--include-other", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    unmatched, kinds_of, sizes = rows(args.zone)
    if not unmatched:
        sys.exit("leads: no unmatched blocked function" + (f" in zone {args.zone}" if args.zone else ""))
    specific = [b for b in unmatched if args.include_other or b["category"] != "other"]
    zones = sorted({b["zone"] for b in unmatched})
    report = {
        "kinds": rank(unmatched, kinds_of, sizes, kind_of),
        "leads": rank(specific, kinds_of, sizes, lead_of, not args.include_other),
        "zones": {z: rank([b for b in specific if b["zone"] == z], kinds_of, sizes, lead_of, not args.include_other)
                  for z in zones},
    }
    if args.json:
        json.dump(report, sys.stdout, indent=1)
        print()
        return
    total = {b["mangled"] for b in unmatched}
    print(f"{len(total)} blocked unmatched functions, {sum(sizes[f] for f in total):,} bytes\n")
    table("By kind of blocker (a function counts under each of its blockers)", report["kinds"], 20, args.by_functions)
    print()
    table("Leads overall" + ("" if args.include_other else " (without `other`)"), report["leads"], args.top, args.by_functions)
    for zone in zones:
        print()
        table(f"Zone {zone}", report["zones"][zone], args.top, args.by_functions)


if __name__ == "__main__":
    main()

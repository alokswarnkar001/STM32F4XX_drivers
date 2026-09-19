"""
Extracts all text from docs/STM32F4xx_RM.pdf into a single cached .txt file,
one page per block, each preceded by a "===PAGE <n>===" marker (n = PDF page
number, 1-indexed, matching the number you'd type into a PDF viewer's page box).

Run once per machine/PDF version; the cache is reused after that (skipped if
already present and not --force). Output lets the rest of the skill use plain
Grep/Read instead of PDF page-image rendering, which requires poppler and
isn't installed on this machine.

Usage:
    python pdf_to_text.py [--force]
"""
import sys
import pathlib
import logging

# pypdf logs a warning per malformed PDF object it encounters; silence that
# noise since RM0090 triggers plenty of it across ~1740 pages.
logging.getLogger("pypdf").setLevel(logging.ERROR)

try:
    import pypdf
except ImportError:
    print("pypdf not installed. Run: pip install pypdf", file=sys.stderr)
    sys.exit(1)

# This file lives at <skill>/scripts/pdf_to_text.py, so parent.parent is <skill>;
# REPO_ROOT walks up three more levels: <skill> -> skills -> .claude -> repo root.
SKILL_DIR = pathlib.Path(__file__).resolve().parent.parent
REPO_ROOT = SKILL_DIR.parent.parent.parent
PDF_PATH = REPO_ROOT / "docs" / "STM32F4xx_RM.pdf"
CACHE_DIR = SKILL_DIR / "cache"
OUT_PATH = CACHE_DIR / "STM32F4xx_RM.txt"


def main():
    force = "--force" in sys.argv

    if not PDF_PATH.exists():
        print(f"PDF not found at {PDF_PATH}", file=sys.stderr)
        sys.exit(1)

    if OUT_PATH.exists() and not force:
        print(f"Cache already exists at {OUT_PATH} (use --force to regenerate)")
        return

    CACHE_DIR.mkdir(parents=True, exist_ok=True)

    reader = pypdf.PdfReader(str(PDF_PATH))
    n = len(reader.pages)
    print(f"Extracting {n} pages from {PDF_PATH.name} ...")

    with open(OUT_PATH, "w", encoding="utf-8") as f:
        for i in range(n):
            text = reader.pages[i].extract_text() or ""
            f.write(f"===PAGE {i + 1}===\n")
            f.write(text)
            f.write("\n")
            if (i + 1) % 200 == 0:
                print(f"  ... {i + 1}/{n}")

    print(f"Done. Wrote {OUT_PATH} ({OUT_PATH.stat().st_size / 1e6:.1f} MB)")


if __name__ == "__main__":
    main()

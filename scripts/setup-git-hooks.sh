#!/bin/sh
# Run once per clone to enable this repo's tracked git hooks
# (scripts/git-hooks/), including the AI-assisted pre-commit review.
set -e
cd "$(git rev-parse --show-toplevel)"
git config core.hooksPath scripts/git-hooks
# Set the executable bit git tracks in its own index (works on Windows too,
# unlike chmod - matters if this repo is ever cloned on Linux/macOS).
git update-index --chmod=+x scripts/git-hooks/pre-commit 2>/dev/null || true
echo "core.hooksPath set to scripts/git-hooks."
echo "Skip the AI review for a single commit with: SKIP_AI_PRECOMMIT=1 git commit ..."

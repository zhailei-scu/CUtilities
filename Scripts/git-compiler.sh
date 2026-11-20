#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
GIT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

GIT_BRANCH=$(git -C "$GIT_ROOT" branch --show-current 2>/dev/null)

GIT_TAG=$(git -C "$GIT_ROOT" describe --tags --abbrev=0 --always 2>/dev/null)

GIT_COMMITID=$(git -C "$GIT_ROOT" rev-parse HEAD 2>/dev/null)

GIT_BRANCH=${GIT_BRANCH:-unknown}

GIT_TAG=${GIT_TAG:-unknown}

GIT_COMMITID=${GIT_COMMITID:-unknown}

set -x

exec "$1" \
    "-DGIT_BRANCH=\"$GIT_BRANCH\"" \
    "-DGIT_TAG=\"$GIT_TAG\"" \
    "-DGIT_COMMITID=\"$GIT_COMMITID\"" \
    "${@:2}"
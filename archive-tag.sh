#!/bin/sh
#
# Create git tags from release archives

ARCHIVE="$1"

BASE="$(basename "$ARCHIVE" .tar.gz)"
VERSION="${BASE#bmake-}"

git rm -r *
tar xzvf "$ARCHIVE" --strip-components=1
git add *
DATE="$(date -Iminutes -r "$ARCHIVE")"

git commit -m "Version $VERSION" --date="$DATE"
git tag "$VERSION"

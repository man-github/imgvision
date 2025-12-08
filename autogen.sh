#!/bin/sh
set -e

echo "Running autoreconf..."
autoreconf --install --force --verbose
echo "Autotools build system generated."

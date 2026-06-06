#!/bin/bash

echo "Validating Swisstrain project structure..."

BASE_DIR="."

# Required directories
REQUIRED_DIRS=(
    "Content"
    "Content/Landscape"
    "Content/Landscape/Heightmaps"
    "Content/Landscape/Materials"
    "Content/Landscape/Textures"
    "Content/Landscape/Water"
    "Content/Landscape/Foliage"
    "Content/Rail"
    "Content/Maps"
    "Source"
    "Source/SwisstrainLandscape"
    "Source/SwisstrainRail"
    "Scripts"
    "Scripts/Build"
    "docs"
    ".github"
    ".github/workflows"
)

# Required files
REQUIRED_FILES=(
    "Swisstrain.uproject"
    "README.md"
    ".gitignore"
    ".gitattributes"
    "Scripts/Build/build.sh"
    "Scripts/Build/build.bat"
    ".github/workflows/build.yml"
    "docs/windows-build-host-setup.md"
)

# Check directories
echo "Checking required directories..."
MISSING_DIRS=()
for dir in "${REQUIRED_DIRS[@]}"; do
    if [ ! -d "$BASE_DIR/$dir" ]; then
        MISSING_DIRS+=("$dir")
    fi
done

# Check files
echo "Checking required files..."
MISSING_FILES=()
for file in "${REQUIRED_FILES[@]}"; do
    if [ ! -f "$BASE_DIR/$file" ]; then
        MISSING_FILES+=("$file")
    fi
done

# Report results
if [ ${#MISSING_DIRS[@]} -eq 0 ] && [ ${#MISSING_FILES[@]} -eq 0 ]; then
    echo "✓ All required directories and files are present"
    exit 0
else
    echo "✗ Validation failed"
    if [ ${#MISSING_DIRS[@]} -gt 0 ]; then
        echo "Missing directories:"
        for dir in "${MISSING_DIRS[@]}"; do
            echo "  - $dir"
        done
    fi
    if [ ${#MISSING_FILES[@]} -gt 0 ]; then
        echo "Missing files:"
        for file in "${MISSING_FILES[@]}"; do
            echo "  - $file"
        done
    fi
    exit 1
fi

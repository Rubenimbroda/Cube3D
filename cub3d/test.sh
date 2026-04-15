#!/bin/bash

# cub3D Test Suite
# Validates mandatory part against subject requirements

TEST_DIR="/tmp/cub3d_tests"
PROGRAM="./cub3D"
PASS=0
FAIL=0

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

mkdir -p "$TEST_DIR"

echo "================================================"
echo "cub3D Test Suite - Mandatory Part Validation"
echo "================================================"
echo ""

# Helper function to create a minimal valid XPM file
create_xpm_file() {
	local path="$1"
	cat > "$path" << 'XPMEOF'
/* XPM */
static char *test[] = {
"2 2 2 1",
"a c #000000",
"b c #FFFFFF",
"ab",
"ba"
};
XPMEOF
}

# Helper function to create a test file
create_test_file() {
	local name="$1"
	shift
	local path="$TEST_DIR/$name"
	printf '%s\n' "$@" > "$path"
	echo "$path"
}

# Helper function to run test
run_test() {
	local name="$1"
	local path="$2"
	local should_pass="$3"
	
	timeout 1 "$PROGRAM" "$path" >/dev/null 2>&1
	local exit_code=$?
	
	# Exit code 0 or 124 (timeout) = acceptance (program started)
	# Exit code 1 = rejection (parser error)
	local accepted=0
	if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ]; then
		accepted=1
	fi
	
	if [ "$should_pass" -eq 1 ]; then
		if [ $accepted -eq 1 ]; then
			echo -e "${GREEN}✓ PASS${NC} - $name (accepted as expected)"
			((PASS++))
		else
			echo -e "${RED}✗ FAIL${NC} - $name (should accept but rejected)"
			((FAIL++))
		fi
	else
		if [ $accepted -eq 0 ]; then
			echo -e "${GREEN}✓ PASS${NC} - $name (rejected as expected)"
			((PASS++))
		else
			echo -e "${RED}✗ FAIL${NC} - $name (should reject but accepted)"
			((FAIL++))
		fi
	fi
}

echo "=== 1. VALID MAPS (should accept and start) ==="
echo ""

# Valid: minimal map
create_xpm_file "$TEST_DIR/north.xpm"
create_xpm_file "$TEST_DIR/south.xpm"
create_xpm_file "$TEST_DIR/west.xpm"
create_xpm_file "$TEST_DIR/east.xpm"
create_test_file "valid_minimal.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Minimal valid map" "$TEST_DIR/valid_minimal.cub" 1

# Valid: random element order
create_test_file "valid_random_order.cub" \
	"SO $TEST_DIR/south.xpm" \
	"" \
	"C 225,30,0" \
	"NO $TEST_DIR/north.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"" \
	"F 220,100,0" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Random element order" "$TEST_DIR/valid_random_order.cub" 1

# Valid: RGB with spaces around commas
create_test_file "valid_rgb_spaces.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220 , 100 , 0" \
	"C 225 , 30 , 0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "RGB with spaces around commas" "$TEST_DIR/valid_rgb_spaces.cub" 1

# Valid: map with leading spaces
create_test_file "valid_map_spaces.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"   11111" \
	"  1N001" \
	"   11111"
run_test "Map with leading spaces" "$TEST_DIR/valid_map_spaces.cub" 1

echo ""
echo "=== 2. INVALID MAPS (should reject with Error) ==="
echo ""

# Invalid: missing closing walls
create_test_file "invalid_open_map.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N000" \
	"11111"
run_test "Map not enclosed by walls" "$TEST_DIR/invalid_open_map.cub" 0

# Invalid: multiple players
create_test_file "invalid_multi_player.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N0E1" \
	"11111"
run_test "Multiple player spawns" "$TEST_DIR/invalid_multi_player.cub" 0

# Invalid: invalid character in map
create_test_file "invalid_char.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N0X1" \
	"11111"
run_test "Invalid character in map" "$TEST_DIR/invalid_char.cub" 0

# Invalid: empty content after map
create_test_file "invalid_content_after_map.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111" \
	"" \
	"11111"
run_test "Non-empty content after map" "$TEST_DIR/invalid_content_after_map.cub" 0

# Invalid: duplicate texture
create_test_file "invalid_dup_texture.cub" \
	"NO $TEST_DIR/north.xpm" \
	"NO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Duplicate texture identifier" "$TEST_DIR/invalid_dup_texture.cub" 0

# Invalid: missing texture
create_test_file "invalid_missing_texture.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Missing texture (EA)" "$TEST_DIR/invalid_missing_texture.cub" 0

# Invalid: missing player spawn
create_test_file "invalid_no_player.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"10001" \
	"11111"
run_test "No player spawn" "$TEST_DIR/invalid_no_player.cub" 0

# Invalid: color out of range
create_test_file "invalid_color_range.cub" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 256,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Color value out of range [0-255]" "$TEST_DIR/invalid_color_range.cub" 0

# Invalid: wrong extension
create_test_file "invalid_extension.txt" \
	"NO $TEST_DIR/north.xpm" \
	"SO $TEST_DIR/south.xpm" \
	"WE $TEST_DIR/west.xpm" \
	"EA $TEST_DIR/east.xpm" \
	"" \
	"F 220,100,0" \
	"C 225,30,0" \
	"" \
	"11111" \
	"1N001" \
	"11111"
run_test "Wrong file extension (.txt)" "$TEST_DIR/invalid_extension.txt" 0

echo ""
echo "=== 3. CLI ARGUMENT VALIDATION ==="
echo ""

# Invalid: no arguments
timeout 1 "$PROGRAM" >/dev/null 2>&1
if [ $? -ne 0 ]; then
	echo -e "${GREEN}✓ PASS${NC} - No arguments returns error"
	((PASS++))
else
	echo -e "${RED}✗ FAIL${NC} - No arguments should return error"
	((FAIL++))
fi

# Invalid: too many arguments
timeout 1 "$PROGRAM" "$TEST_DIR/valid_minimal.cub" extra >/dev/null 2>&1
if [ $? -ne 0 ]; then
	echo -e "${GREEN}✓ PASS${NC} - Too many arguments returns error"
	((PASS++))
else
	echo -e "${RED}✗ FAIL${NC} - Too many arguments should return error"
	((FAIL++))
fi

echo ""
echo "================================================"
echo -e "Test Results: ${GREEN}$PASS passed${NC}, ${RED}$FAIL failed${NC}"
echo "================================================"

if [ $FAIL -eq 0 ]; then
	echo -e "${GREEN}All tests passed!${NC}"
	exit 0
else
	echo -e "${RED}Some tests failed. Review the output above.${NC}"
	exit 1
fi

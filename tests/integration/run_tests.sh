#!/bin/bash

# テスト用ディレクトリとプログラムの設定
TEST_DIR="$(dirname "$0")"
TEST_CASES_DIR="$TEST_DIR/test_cases"
EXPECTED_OUTPUT_DIR="$TEST_DIR/expected_output"
PROGRAM="../../cub3D"

# 色の設定
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

# テスト結果のカウンタ
PASSED=0
FAILED=0
TOTAL=0

# テスト関数
run_test() {
    local test_file="$1"
    local expected_output_file="$2"
    local test_name="$(basename "$test_file")"
    
    echo "Running test: $test_name"
    TOTAL=$((TOTAL+1))
    
    # プログラムを実行し、出力を取得
    output=$($PROGRAM "$test_file" 2>&1)
    exit_code=$?
    
    # 期待される出力を取得
    if [ -f "$expected_output_file" ]; then
        expected=$(cat "$expected_output_file")
        
        # 出力を比較
        if [ "$output" = "$expected" ] && [ "$exit_code" -eq "$(head -n1 "$expected_output_file.exit")" ]; then
            echo -e "${GREEN}✓ PASSED${RESET}: $test_name"
            PASSED=$((PASSED+1))
        else
            echo -e "${RED}✗ FAILED${RESET}: $test_name"
            echo "Expected output:"
            echo "$expected"
            echo "Actual output:"
            echo "$output"
            echo "Expected exit code: $(head -n1 "$expected_output_file.exit")"
            echo "Actual exit code: $exit_code"
            FAILED=$((FAILED+1))
        fi
    else
        echo -e "${RED}✗ ERROR${RESET}: Missing expected output file for $test_name"
        FAILED=$((FAILED+1))
    fi
    
    echo "---------------------------------"
}

# テスト実行開始
echo "Starting integration tests..."

# 正常系テスト
echo "== Running valid test cases =="
for test_file in "$TEST_CASES_DIR/valid"/*.cub; do
    if [ -f "$test_file" ]; then
        expected_file="$EXPECTED_OUTPUT_DIR/valid/$(basename "$test_file")"
        run_test "$test_file" "$expected_file"
    else
        echo "No valid test cases found."
    fi
done

# 異常系テスト (ファイル形式エラー)
echo "== Running invalid file format test cases =="
for test_file in "$TEST_CASES_DIR/invalid/file_format"/*; do
    if [ -f "$test_file" ]; then
        expected_file="$EXPECTED_OUTPUT_DIR/invalid/file_format/$(basename "$test_file")"
        run_test "$test_file" "$expected_file"
    else
        echo "No invalid file format test cases found."
    fi
done

# その他のエラーテスト（テクスチャ、色指定、マップなど）
for error_type in texture color map; do
    echo "== Running invalid $error_type test cases =="
    for test_file in "$TEST_CASES_DIR/invalid/$error_type"/*; do
        if [ -f "$test_file" ]; then
            expected_file="$EXPECTED_OUTPUT_DIR/invalid/$error_type/$(basename "$test_file")"
            run_test "$test_file" "$expected_file"
        else
            echo "No invalid $error_type test cases found."
        fi
    done
done

# テスト結果の表示
echo "==================================="
echo "Test results: $PASSED/$TOTAL passed"
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${RESET}"
else
    echo -e "${RED}$FAILED tests failed.${RESET}"
    exit 1
fi

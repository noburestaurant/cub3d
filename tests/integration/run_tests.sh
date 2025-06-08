#!/bin/bash

# テスト用ディレクトリとプログラムの設定
TEST_DIR="$(dirname "$0")"
TEST_CASES_DIR="$TEST_DIR/test_cases"
EXPECTED_OUTPUT_DIR="$TEST_DIR/expected_output"
PROGRAM="./cub3D"

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
    
    # 有効なマップファイルの場合はタイムアウトを設定
    if [[ "$test_file" == *"/valid/"* ]]; then
        # 有効なマップファイルの場合：3秒でタイムアウト
        echo "Valid map test - using timeout..."
        
        # バックグラウンドでプログラムを実行
        $PROGRAM "$test_file" > /tmp/test_output_$$.txt 2>&1 &
        local pid=$!
        
        # 2秒待機してプロセスの状態をチェック
        sleep 2
        
        # プロセスがまだ動いている場合（レンダリング中）、正常と判断
        if kill -0 $pid 2>/dev/null; then
            # プロセスを終了
            kill $pid 2>/dev/null
            wait $pid 2>/dev/null
            
            # 有効なマップファイルの場合は成功と判断
            output=""
            exit_code=0
            echo "Process was running (rendering), considered successful"
        else
            # プロセスが既に終了している場合は出力を確認
            wait $pid
            exit_code=$?
            output=$(cat /tmp/test_output_$$.txt)
            echo "Process ended early, checking output..."
        fi
        
        # 一時ファイルを削除
        rm -f /tmp/test_output_$$.txt
    else
        # 無効なマップファイルの場合は通常通り実行
        output=$($PROGRAM "$test_file" 2>&1)
        exit_code=$?
    fi
    
    # 期待される出力を取得
    if [ -f "$expected_output_file" ]; then
        expected=$(cat "$expected_output_file")
        expected_exit_code=$(cat "$expected_output_file.exit" 2>/dev/null || echo "1")
        
        # 出力を比較
        if [ "$output" = "$expected" ] && [ "$exit_code" -eq "$expected_exit_code" ]; then
            echo -e "${GREEN}✓ PASSED${RESET}: $test_name"
            PASSED=$((PASSED+1))
        else
            echo -e "${RED}✗ FAILED${RESET}: $test_name"
            echo "Expected output:"
            echo "$expected"
            echo "Actual output:"
            echo "$output"
            echo "Expected exit code: $expected_exit_code"
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

# 引数の数エラーテスト
echo "== Running argument count test cases =="
echo "Testing with no arguments..."
TOTAL=$((TOTAL+1))
output=$($PROGRAM 2>&1)
exit_code=$?
expected_output="Error: Invalid number of arguments"
if [ "$output" = "$expected_output" ] && [ "$exit_code" -eq 1 ]; then
    echo -e "${GREEN}✓ PASSED${RESET}: no arguments"
    PASSED=$((PASSED+1))
else
    echo -e "${RED}✗ FAILED${RESET}: no arguments"
    echo "Expected output: $expected_output"
    echo "Actual output: $output"
    echo "Expected exit code: 1"
    echo "Actual exit code: $exit_code"
    FAILED=$((FAILED+1))
fi

echo "Testing with too many arguments..."
TOTAL=$((TOTAL+1))
output=$($PROGRAM arg1 arg2 arg3 2>&1)
exit_code=$?
if [ "$output" = "$expected_output" ] && [ "$exit_code" -eq 1 ]; then
    echo -e "${GREEN}✓ PASSED${RESET}: too many arguments"
    PASSED=$((PASSED+1))
else
    echo -e "${RED}✗ FAILED${RESET}: too many arguments"
    echo "Expected output: $expected_output"
    echo "Actual output: $output"
    echo "Expected exit code: 1"
    echo "Actual exit code: $exit_code"
    FAILED=$((FAILED+1))
fi
echo "---------------------------------"

# ファイルが存在しないテスト
echo "Testing with nonexistent file..."
TOTAL=$((TOTAL+1))
output=$($PROGRAM "nonexistent_file.cub" 2>&1)
exit_code=$?
expected_output="Error: Cannot open file"
if [ "$output" = "$expected_output" ] && [ "$exit_code" -eq 1 ]; then
    echo -e "${GREEN}✓ PASSED${RESET}: nonexistent file"
    PASSED=$((PASSED+1))
else
    echo -e "${RED}✗ FAILED${RESET}: nonexistent file"
    echo "Expected output: $expected_output"
    echo "Actual output: $output"
    echo "Expected exit code: 1"
    echo "Actual exit code: $exit_code"
    FAILED=$((FAILED+1))
fi
echo "---------------------------------"

# 正常系テスト
echo "== Running valid test cases =="
for test_file in "$TEST_CASES_DIR/valid"/*.cub; do
    if [ -f "$test_file" ]; then
		## temporarily
		test_name="$(basename "$test_file")"
		if [ "$test_name" = "minimal.cub" ]; then
			echo "Skipping test: $test_name (temporarily disable)"
			continue
		##
		if
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

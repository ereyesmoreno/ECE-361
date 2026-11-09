#!/usr/bin/env bash

echo "=== Running Scenario Regression Tests ==="
fails=0

for sc in scenarios/*.txt; do
    # Skip loop if no txt files match
    [ -e "$sc" ] || continue

    base=$(basename "$sc" .txt)
    exp="expected/${base}.trace"

    if [ -f "$exp" ]; then
        echo -n "Testing $sc... "
        ./replay "$sc" > "tmp_${base}.out" 2>&1

        if diff -u "$exp" "tmp_${base}.out" > /dev/null; then
            echo "PASS"
        else
            echo "FAIL (output does not match $exp)"
            diff -u "$exp" "tmp_${base}.out"
            fails=$((fails + 1))
        fi
        rm -f "tmp_${base}.out"
    else
        echo "Testing $sc... FAIL (missing $exp)"
        fails=$((fails + 1))
    fi
done

if [ "$fails" -ne 0 ]; then
    echo "=== REGRESSION FAILED ($fails failures) ==="
    exit 1
fi

echo "=== ALL REGRESSION TESTS PASSED ==="
exit 0
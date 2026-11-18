#!/bin/sh

pass=0
fail=0

for file in inputs/*.txt; do
    name=$(basename "$file" .txt)          # inputs/mismatch.txt -> mismatch
    
    actual=$(./balance < "$file")
    status=$?
    
    want=$(cat "expected/$name.out")
    want_status=$(cat "expected/$name.status")
    
    if [ "$actual" = "$want" ] && [ "$status" = "$want_status" ]; then
        echo "PASS $name"
        pass=$((pass + 1))
    else
        echo "FAIL $name"
        echo "  expected: $want (exit $want_status)"
        echo "  got:      $actual (exit $status)"
        fail=$((fail + 1))
    fi
done

echo "regress: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
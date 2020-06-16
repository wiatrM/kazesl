#!/bin/sh

echo "Generating baseline coverage data file."
lcov --capture --initial --directory build --output-file coverage_base.info
echo "Generating coverage based on executed tests."
lcov --capture --directory build --output-file coverage_test.info
echo "Merging coverage tracefiles."
lcov --add-tracefile coverage_base.info --add-tracefile coverage_test.info --output-file coverage_merge.info
echo "Removing unwanted files from coverage."
lcov --remove coverage_merge.info "`pwd`/external/*" "/include/*" "/usr/*" -o coverage.info

#!/bin/bash

echo "TESTING INDEXER.C"

echo "Test with NULL parameters"
./indexer null null 

echo "Test with valid parameters"
./indexer ../crawler/crawlerTest/ ./indexertest1

echo "Test with invalid (non-existant) directory"
./indexer ../something_invalid/ ./indexertest2

echo "Test with invalid (non-crawler) directory"
./indexer ../crawler/ ./indexertest3


echo "END OF TESTING"

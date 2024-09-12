#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H

class NaturalMergeSorter {
public:
    virtual int GetSortedRunLength(int* array, int arrayLength, int startIndex) {
        // Special case if startIndex >= arrayLength
        if (startIndex >= arrayLength) {
            return 0;
        }

        // A run of length 1 is always sorted, so initialize length to 1
        int length = 1;
        for (int i = startIndex + 1; i < arrayLength; i++) {
            // If element at i is less than element at i - 1, then the sorted run
            // has ended
            if (array[i] < array[i - 1]) {
                return length;
            }
            length++;
        }

        return length;
    }

    virtual void NaturalMergeSort(int* array, int arrayLength) {
        int i1 = 0;
        int run1Length = GetSortedRunLength(array, arrayLength, i1);
        while (run1Length < arrayLength) {
            // Compute the second run's starting index
            int i2 = i1 + run1Length;

            // If i2 equals the array's length, then the run starting at i1 goes
            // up to, and includes, the array's last item.
            if (i2 == arrayLength) {
                // Reset i1 to the start of the array
                i1 = 0;
            }
            else {
                // Determine run 2's length
                int run2Length = GetSortedRunLength(array, arrayLength, i2);

                // Merge the two runs
                Merge(array, i1, i2 - 1, i2 + run2Length - 1);

                // Move run1's starting index for the next pass
                i1 = i2 + run2Length;

                // Reset i1 to 0 if array's end is reached
                if (i1 == arrayLength) {
                    i1 = 0;
                }
            }

            // Compute first run's length for next pass
            run1Length = GetSortedRunLength(array, arrayLength, i1);
        }
    }

    virtual void Merge(int* numbers, int leftFirst, int leftLast,
        int rightLast) {
        int mergedSize = rightLast - leftFirst + 1;
        int* mergedNumbers = new int[mergedSize];
        int mergePos = 0;
        int leftPos = leftFirst;
        int rightPos = leftLast + 1;

        // Add smallest element from left or right partition to merged numbers
        while (leftPos <= leftLast && rightPos <= rightLast) {
            if (numbers[leftPos] <= numbers[rightPos]) {
                mergedNumbers[mergePos] = numbers[leftPos];
                leftPos++;
            }
            else {
                mergedNumbers[mergePos] = numbers[rightPos];
                rightPos++;
            }
            mergePos++;
        }

        // If left partition isn't empty, add remaining elements to mergedNumbers
        while (leftPos <= leftLast) {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
            mergePos++;
        }

        // If right partition isn't empty, add remaining elements to mergedNumbers
        while (rightPos <= rightLast) {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
            mergePos++;
        }

        // Copy merged numbers back to numbers
        for (mergePos = 0; mergePos < mergedSize; mergePos++) {
            numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
        }

        // Free temporary array
        delete[] mergedNumbers;
    }
};

#endif

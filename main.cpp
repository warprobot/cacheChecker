#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

#define TEST_CASE_QNT 20
#define IS_RANDOM true
#define TWICE(x) x x
#define x64(x) TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(x))))))))
#define KB 1024
#define MB KB * KB

struct element {
    long nPad[7]; // magic number - nPAD: [0, 31] => more is worse
    element *next;
    element(){ this->next = nullptr;}
};

int myrandom (int i) { return std::rand()%i;}

void array2list(element * head, std::vector<int> arr){
    /*
        helper func helper vector to array
    */
    int i = 0;
    for (int j = i + 1; j < arr.size(); j++, i++){
        head[arr[i]].next = &head[arr[j]];
    }
    head[arr[i]].next = &head[arr[0]];

}

double testCase(element *e){
    element *b = e;
    int N = 10000;

    // start timer
    clock_t start = clock();
    for (int i = 0; i < N; i++){
        x64(b = b->next;);
    }
    // finish timer
    clock_t finish = clock();

    double result = ((double((finish - start)) / (N * 64)) / CLOCKS_PER_SEC) * 1000000000;
    return result;
}

double median(std::vector<double> &arr){
    double sum = 0;
    for (int i = 0; i < arr.size(); i++){
        sum += arr[i];
    }
    return sum/arr.size();
}

int main() {
    std::cout << sizeof(element) << std::endl;
    for (int i = 1 * KB; i < 16 * MB; i *= 1.15){

        std::cout << (double) i/KB << "\t";

        size_t N = i/ sizeof(element);
        std::vector<int> arr;
        for (int j = 0; j < N; j++) {
            arr.push_back(j);
        }

        if (IS_RANDOM) {
            std::random_shuffle(arr.begin(), arr.end(), myrandom);
        }

        element * head = new element[N];
        array2list(head, arr);

        std::vector <double> results;
        for (int j = 0; j < TEST_CASE_QNT; j++) {
            results.push_back(testCase(head));
        }
        std::cout << median(results) << std::endl;
        free(head);
    }

    return 0;
}

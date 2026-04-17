// ==========================================
// N = 100000, M = 100000
// Array-based Max PQ time: 48.7917 seconds
// Heap-based Max PQ time: 0.0313608 seconds
// ==========================================

#include <iostream> 
#include <vector>   
#include <random>   // 난수생성기(mt19937)와 균등분포(uniform_real_distribution)
#include <chrono>   // 실행 시간 측정을 위한 헤더 

using namespace std;
using namespace std::chrono; // 시간 측정에 필요한 네임스페이스

// ============================================================
// 1. 배열 기반 최대 우선순위 큐
// ============================================================
class ArrayMaxPQ {
    private:
        // 실제 데이터를 저장하는 정렬되지 않은 배열
        vector<int> data;

    public:
        // 원소 삽입: 배열 맨 뒤에 그냥 추가하면 됨
        void add(int x) {data.push_back(x);}

        // 최대값 삭제 및 반환
        int extractMax() {
            // 최대값의 위치를 저장할 변수
            // 처음에는 0번 원소가 최대라고 가정하고 시작
            int maxIndex = 0;

            // 전체 배열을 순회하면서 최대값 위치를 찾음
            for (int i = 1; i < (int)data.size(); i++) {        // (int)로 형변환한 이유: data.size()는 size_t 타입이므로, int로 변환하여 비교해야 함
                if (data[i] > data[maxIndex]) {maxIndex = i;} // 최대값 위치 갱신
            }

            // 최대값을 따로 저장해둠 (나중에 반환해야 하므로)
            int maxValue = data[maxIndex];

            // 배열 중간에 빈칸이 생기지 않도록 
            // 마지막 원소를 최대값이 있던 위치로 옮김
            data[maxIndex] = data.back();

            // 마지막 원소 제거
            data.pop_back();

            // 삭제된 최대값 반환
            return maxValue;
        }

        // 큐가 비어 있는지 확인
        bool empty() const {return data.empty();}
};

// ============================================================
// 2. 힙 기반 최대 우선순위 큐
// ============================================================
class HeapMaxPQ {
    private:
    // 힙을 배열(vector)로 구현
    vector<int> heap;

    // 삽입 후, 새 원소를 위로 올리며 최대 힙 성질을 복구
    void siftUp(int index) {
        // 루트가 아닐 동안 반복
        while (index > 0) {
            // 부모 인덱스 계산
            int parent = (index - 1) / 2;

            // 부모가 자식보다 크거나 같으면 최대 힙 조건 만족
            if (heap[parent] >= heap[index]) {break;}

            // 부모보다 자식이 더 크면 자리 교환
            swap(heap[parent], heap[index]);

            // 교환 후, 검사 위치를 부모로 이동
            index = parent;
        }
    }

    // 삭제 후, 루트 원소를 아래로 내리며 최대 힙 성질을 복구
    void siftDown(int index) {
        int n = heap.size();

        while (true) {
            // 왼쪽 자식 인덱스
            int left = 2 * index + 1;

            // 오른쪽 자식 인덱스
            int right = 2 * index + 2;

            // 현재는 일단 자기 자신이 가장 크다고 가정
            int largest = index;

            // 왼쪽 자식이 존재하고, 현재 후보보다 더 크면 largest 갱신
            if (left < n && heap[left] > heap[largest]) {largest = left;}

            // 오른쪽 자식이 존재하고, 현재 후보보다 더 크면 largest 갱신
            if (right < n && heap[right] > heap[largest]) {largest = right;}

            // 자기 자신이 가장 크다면 더 내려갈 필요 없음
            if (largest == index) {break;}

            // 더 큰 자식과 자리 교환
            swap(heap[index], heap[largest]);

            // 교환 후, 그 자식 위치에서 계속 검사
            index = largest;
        }
    }

    public:
        // 원소 삽입
        void add(int x) {
            // 일단 맨 뒤에 삽입
            heap.push_back(x);

            // 최대 힙 성질이 깨졌을 수 있으므로 위로 올림
            siftUp((int)heap.size() - 1);
        }

        // 최대값 삭제 및 반환
        int extractMax() {
            // 최대 힙에서는 루트(0번 인덱스)가 최대값
            int maxValue = heap[0]; 

            // 마지막 원소를 루트로 가져옴
            heap[0] = heap.back();

            // 마지막 원소 제거
            heap.pop_back();

            // 아직 힙에 원소가 남아 있다면 아래로 내리기 수행
            if (!heap.empty()) {siftDown(0);}

            // 삭제된 최대값 반환
            return maxValue;
        }

        // 큐가 비어 있는지 확인
        bool empty() const {return heap.empty();}
};

// ============================================================
// 3. 연산 하나를 저장하기 위한 구조체
// ============================================================
// type: 
//   0 -> add 연산
//   1 -> extractMax 연산
//
// value:
//   add 연산일 때 삽입할 값 
//   extractMax 연산일 때는 사용하지 않으므로 0으로 뒤도 됨 
struct Operation {
    int type;
    int value;
};

// ============================================================
// 4. 동일한 연산 시퀀스를 미리 생성하는 함수
// ============================================================
// 이 함수가 공정한 비교의 핵심
// 
// N개를 먼저 삽입,
// 이후 M번 동안 삽입 또는 삭제 연산을 랜덤하게 결정
// 그 결과를 vector<Operation>에 저장
//
// 이렇게 저장된 연산 목록을 
// 배열 기반 PQ와 힙 기반 PQ에 똑같이 적용
vector<Operation> generateOperations(int N, int M, unsigned seed) {
    // 고정된 seed를 가진 난수 생성기
    // seed가 같으면 항상 같은 랜덤 결과가 나옴
    mt19937 rng(seed); 
        // Mersenne Twister 난수 생성기 - C++11에서 도입된 고성능 난수 생성기
    
    // 삽입할 정수는 0 ~ N 범위에서 랜덤 생성
    uniform_int_distribution<int> valueDist(0, N); 
        // uniform_int_distribution는 균등한 정수 분포를 생성하는 클래스 

    // 연산 종류는 0(add) 또는 1(extract) 중 랜덤 생성;
    uniform_int_distribution<int> typeDist(0, 1);

    // 생성된 연산들을 저장할 벡터
    vector<Operation> ops;

    // 대략 N+M개 정도 연산이 들어갈 것이므로 미리 공간 확보
    // (없더도 되지만 성능상 조금 유리)
    ops.reserve(N + M);

    // -------------------------
    // (1) 초기 N개 삽입 연산 생성
    // -------------------------
    for (int i = 0; i < N; i++) {
        // type = 0 이므로 add 연산
        // valueDist(rng)로 랜덤 값 생성
        ops.push_back({0, valueDist(rng)});
    }

    // 현재 큐 크기를 추적하는 변수
    // 처음에 N개를 삽입했으므로 크기는 N
    int currentSize = N; 

    // -------------------------
    // (2) 이후 M개 연산 생성 
    // -------------------------
    for (int i = 0; i < M; i++) {
        // 0 또는 1을 랜덤으로 뽑아서
        // add / extractMax 여부를 결정
        int opType = typeDist(rng);

        // 큐가 비어 있으면 extractMax를 할 수 없으므로
        // 무조건 add 연산을 넣어야 한다.
        //
        // 또는 랜덤 결과가 0이면 add 연산 생성
        if (currentSize == 0 || opType == 0) {
            ops.push_back({0, valueDist(rng)}); // add(value)
            currentSize++;                      // 삽입했으므로 크기 증가
        }
        else {
            ops.push_back({1, 0});              // extractMax()
                // value는 사용 안 하므로 0으로 넣어도 됨
            currentSize--;                      // 삭제했으므로 크기 감소
        }
    }

    // 완성된 연산 목록 반환
    return ops;
}

// ============================================================
// 5. 동일한 연산 목록을 배열 기반 PQ에 적용해서 시간 측정
// ============================================================
double testArrayPQ(const vector<Operation>& ops) {
    // 배열 기반 PQ 객체 생성
    ArrayMaxPQ pq;

    // 시작 시각 기록
    auto start = high_resolution_clock::now();

    // 미리 생성된 연산들을 순서대로 하나씩 수행
    for (const auto& op : ops) {
        // type이 0이면 add 연산
        if (op.type == 0) {pq.add(op.value);}
        // type이 1이면 extractMax 연산
        else {pq.extractMax();}
    }

    // 종료 시각 기록
    auto end = high_resolution_clock::now();

    // 두 시각의 차이를 초 단위 실수로 계산
    duration<double> diff = end - start;

    // 실행 시간(초) 반환
    return diff.count();
}

// ============================================================
// 6. 동일한 연산 목록을 힙 기반 PQ에 적용해서 시간 측정
// ============================================================
double testHeapPQ(const vector<Operation>& ops) {
    // 힙 기반 PQ 객체 생성
    HeapMaxPQ pq;

    // 시작 시각 기록
    auto start = high_resolution_clock::now();

    // 배열 기반과 완전히 같은 연산 목록을 그대로 수행
    for (const auto& op : ops) {
        if (op.type == 0) {pq.add(op.value);}
        else {pq.extractMax();}
    }

    // 종료 시각 기록
    auto end = high_resolution_clock::now();

    // 걸린 시간 계산
    duration<double> diff = end - start;

    // 실행 시간 반환
    return diff.count();
}

// ============================================================
// 7. main 함수
// ============================================================
int main() {
    // 문제에서 요구한 값
    const int N = 100000;
    const int M = 100000;

    // 같은 시드로 연산 시퀀스를 생성하기 위한 seed 
    // 같은 seed를 쓰면 같은 랜덤 연산 시퀀스를 재현 가능
    const unsigned seed = 12345;

    // --------------------------------------------------------
    // 핵심:
    // 먼저 "연산 목록"을 한 번만 생성
    // --------------------------------------------------------
    vector<Operation> ops = generateOperations(N, M, seed);

    // 생성된 동일한 연산 목록을 배열 기반 PQ에 적용
    double arrayTime = testArrayPQ(ops);

    // 똑같은 연산 목록을 힙 기반 PQ에 적용
    double heapTime = testHeapPQ(ops);

    // 결과 출력
    cout << "N = " << N << ", M = " << M << "\n";
    cout << "Array-based Max PQ time: " << arrayTime << " seconds\n";
    cout << "Heap-based Max PQ time: " << heapTime << " seconds\n";

    return 0;
}
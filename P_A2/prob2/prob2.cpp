#include <iostream>     // cout, cin, getline
#include <fstream>      // ifstream
#include <sstream>      // stringstream을 사용하여 문자열을 분리하기 위한 헤더
#include <vector>       // vector 동적 배열 사용
#include <string>       // string 자료형 사용
#include <algorithm>    // sort 함수
#include <cctype>       // isspace 함수

using namespace std;   

// 한 사람의 주소록 정보를 저장할 구조체
struct Person {
    string name;       
    string company;     
    string address;     
    string zipcode;     // 우편번호
    string phone;      
    string email;       
};

// 문자열의 양쪽 끝에 있는 공백/탭/개행 등을 제거하는 함수
string trim(const string& str) {
    int start = 0;                              // 앞쪽에서 공백이 끝나는 위치를 찾기 위한 인덱스

    // 문자열 앞부분의 공백들을 건너뛰기
    while (start < str.size() && isspace(str[start])) { start++;}

    int end = str.size() - 1;                   // 뒤쪽에서 실제 내용이 끝나는 위치 

    // 뒤쪽 공백들 건너뛰기
    while (end >= start && isspace(str[end])) { end--; }

    // 앞뒤 공백을 제외한 부분만 잘라서 반환
    return str.substr(start, end - start + 1);  // substr(start, length) - start부터 length만큼 잘라서 반환. 
    // 여기서는 end - start + 1이 실제 내용의 길이가 된다.
}

// 주소록 파일의 한 줄을 Person 객체 하나로 바꾸는 함수 
bool parseLine(const string& line, Person& p) {
    vector<string> fields;  // '|'로 나눈 각 필드를 저장할 벡터
    string token;           // 잘라낸 필드를 임시 저장할 문자열 
    stringstream ss(line);  // 한 줄 문자열을 분해하기 위한 스트림 

    // '|'를 기준으로 문자열 잘라내기
    while (getline(ss, token, '|')) {   // getline(스트림, 토큰을 저장할 변수, 구분자) - 구분자까지 읽어서 토큰에 저장
        // 각 필드의 앞뒤 공백을 제거한 뒤 저장
        fields.push_back(trim(token));
    }

    // 문제 조건상 필드는 정확히 6개여야 한다.
    if (fields.size() != 6) {
        return false;
    }

    // 각 필드를 Person 구조체의 멤버에 저장
    p.name = fields[0];
    p.company = fields[1];
    p.address = fields[2];
    p.zipcode = fields[3];
    p.phone = fields[4];
    p.email = fields[5];

    return true; // 성공적으로 파싱했음을 나타내는 true 반환 
}

// 파일을 읽어 전체 주소록을 people 벡터에 저장하는 함수 
bool readFile(const string& filename, vector<Person>& people) { // const: 이 함수는 해당 파라미터를 읽기만 할 것임(원본은 절대 안 건드림). 
    ifstream fin(filename); // 파일 열기
    if (!fin) return false;

    people.clear();         // 기존 데이터가 있으면 비우고 새로 읽기
    
    string line;            // 파일에서 한 줄씩 읽을 문자열

    // 파일 끝까지 한 줄씩 읽는다.
    while (getline(fin, line)) {
        if (trim(line).empty()) continue; // 빈 줄은 건너띄기

        Person p; // 한 줄을 저장할 Person 객체

        // 한 줄 파싱에 성공하면 벡터에 추가하기
        if (parseLine(line, p)) { people.push_back(p); }
    }

    fin.close(); // 파일 닫기
    return true; // 성공적으로 파일을 읽었음을 나타내는 true 반환
}

// Name 기준으로 오름차순 정렬하는 함수
void sortByName(vector<Person>& people) {
    sort(people.begin(), people.end(),     // sort 함수 - people 벡터의 시작부터 끝까지, 비교 기준은 람다 함수로 정의
    [](const Person& a, const Person& b) { // []: 람다 함수 - sort 함수에 비교 기준을 직접 정의하기 위해 사용.
        return a.name < b.name; // 이름을 기준으로 오름차순 비교 
    });
}

// Address 기준으로 오름차순 정렬하는 함수
void sortByAddress(vector<Person>& people) {
    sort(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.address < b.address; // 주소를 기준으로 오름차순 비교 
        });
}

// 현재 저장된 주소록 전체를 출력하는 함수
void printPeople(const vector<Person>& people) {
    for (const Person& p : people) {
        cout << p.name << '\n';
        cout << "Company: " << p.company << '\n';
        cout << "Address: " << p.address << '\n';
        cout << "Zipcode: " << p.zipcode << '\n';
        cout << "Phones: " << p.phone << '\n';
        cout << "Email: " << p.email << "\n";
        cout << '\n'; // 사람 한 명 출력 후 한 줄 띄우기. 
    }
}

int main() {
    vector<Person> people; // 전체 주소록 데이터를 저장할 벡터 
    string command;        // 사용자가 입력하는 명령어 

    // exit 명령이 들어올 때까지 반복
    while (true) {
        cout << "$ ";             // 프롬프트 출력
        getline(cin, command);   // 명령어 한 줄 입력 
        // getline(cin, 변수) - 한 줄 전체를 읽어서 변수에 저장. 
        // cin >> 변수는 공백 전까지만 읽는다.
        command = trim(command); // 명령어 양쪽 공백 제거 

        // "read "로 시작하면 파일 읽기 명령
        if (command.rfind("read ", 0) == 0) { 
            //rfind(찾을 문자열, 시작 인덱스) - 찾을 문자열이 시작 인덱스부터 시작해서 처음 나오는 위치를 반환.
            
            // "read " 다음 부분을 파일명으로 사용
            string filename = trim(command.substr(5)); 
            // substr(시작 인덱스) - 시작 인덱스부터 끝까지 잘라서 반환.

            // 파일 열기에 실패하면 에러 메시지를 출력한다.
            if (!readFile(filename, people)) { cout << "File open error\n"; }
        }
        // 이름 기준 정렬
        else if (command == "sort -name") { sortByName(people); }
        // 주소 기준 정렬
        else if (command == "sort -address") { sortByAddress(people); }
        // 전체 출력
        else if (command == "print") { printPeople(people); }
        // 프로그램 종료
        else if (command == "exit") { break; }
    }

    return 0; 
}
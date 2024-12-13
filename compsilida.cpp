//라이브러리
//순서대로 표준 입출력,파일 입출력, 문자열 스트림 처리, 동적배열위한 벡ㅌ,문자열 처리,예외처리
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>

// 추상 클래스
class BaseSalary {
public:
    virtual void display() const = 0; // 가상함수 만들기
    virtual ~BaseSalary() = default; // 가상 소멸자!
};

// FutureSalary 클래스-급여 데이터 나타냄
class FutureSalary : public BaseSalary {
private:
    int year; //  연도 저장  
    std::string experience; // 경력 수준
    std::string region; // 근무 지역
    int salary; // 연봉
    double growthRate; //연봉증가
public:
    // 생성자: 클래스 멤버 변수를 초기화

    FutureSalary(int year, const std::string& experience, const std::string& region, int salary, double growthRate)
        : year(year), experience(experience), region(region), salary(salary), growthRate(growthRate) {
    }

    // Getter 함수: 클래스 멤버변수 값 반환
    int getYear() const { return year; } // 연도 반환
    std::string getExperience() const { return experience; } // 경력반환
    std::string getRegion() const { return region; } // 지역 반환
    int getSalary() const { return salary; } // 연봉 반환
    double getGrowthRate() const { return growthRate; } // 연봉증강ㅠㄹ반환

    // 연산자 오버로딩- 연산자 재정의,객체 데이터츨력
    friend std::ostream& operator<<(std::ostream& os, const FutureSalary& fs) {
        os << "Year: " << fs.year
            << ", Experience: " << fs.experience
            << ", Region: " << fs.region
            << ", Salary: " << fs.salary
            << ", Growth Rate: " << fs.growthRate;
        return os;
    }

    // display 함수-객체정보출력
    void display() const override {
        std::cout << *this << std::endl;
    }
};

// CSV열고 데이터 읽기
void loadDataFromCSV(const std::string& filename, std::vector<FutureSalary>& data) {
    std::ifstream infile(filename); // 파일 입력 스트림 생성
    if (!infile) { // 파일 열기에 실패했을때
        std::cerr << "파일 오픈 실패: " << filename << std::endl;
        throw std::ios_base::failure("파일을 열 수 없습니다: " + filename);
    } //파일 열 수 없다고 출력하기

    std::string line; // 파일의 각 줄을 저장할 문자열
    bool isHeader = true; // 첫째줄-해더로 처리
    while (std::getline(infile, line)) { //한 줄씩 읽음
        if (isHeader) { //
            isHeader = false; //첫줄은 안 읽고 건너뛰기
            continue;
        }

        std::stringstream ss(line); // 데이터 한줄한줄 처리하는 문자열 스트림
        std::string token; // 데이터를 임시 저장할 문자열 변수
        int year;
        std::string experience;
        std::string region;
        int salary;
        double growthRate;

        try {
            // Year 열 읽기
            std::getline(ss, token, ',');
            year = std::stoi(token); // 문자열을 정수로 변환

            // Experience 열 읽기
            std::getline(ss, token, ',');
            experience = token; // 문자열 그대로 저장

            // Region 열 읽기
            std::getline(ss, token, ',');
            region = token; // 문자열 그대로 저장

            // Salary 열 읽기
            std::getline(ss, token, ',');
            salary = std::stoi(token); // 문자열을 정수로 변환

            // GrowthRate 열 읽기
            std::getline(ss, token, ',');
            growthRate = std::stod(token); // 문자열을 실수로 변환

            // FutureSalary 객체생성해서 벡터에 추가하기
            data.emplace_back(year, experience, region, salary, growthRate);
        }
        catch (const std::exception& e) {  //만약 파싱 중 오류발생했을때
            std::cerr << "파싱 오류: " << e.what() << " (행 데이터: " << line << ")" << std::endl;
        }
    }
    infile.close(); // 파일 닫기
}

int main() {
    std::vector<FutureSalary> salaryData; // FutureSalary객체를 저장할 벡터

    try {
        const std::string inputFilePath = "C:\\Users\\이수인\\OneDrive\\바탕 화면\\salarydata.csv"; //파일경로

        std::cout << "사용 중인 파일 경로: " << inputFilePath << std::endl;

        // CSV 파일 읽기
        loadDataFromCSV(inputFilePath, salaryData);

        std::cout << "CSV 파일을 성공적으로 읽었습니다." << std::endl;
        for (const auto& record : salaryData) {
            record.display(); //객체데이터출력
        }
    }
    catch (const std::exception& e) { // 예외 처리
        std::cerr << "오류 발생: " << e.what() << std::endl;
    }

    return 0; // 프로그램 종료
}

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "사용법: " << argv[0] << " <file1> <file2>\n";
        return 1;
    }

    // 첫 번째 파일에서 숫자를 읽어옵니다.
    FILE *file1 = fopen(argv[1], "rb");
    if (!file1) {
        std::cerr << "첫 번째 파일을 열 수 없습니다.\n";
        return 1;
    }

    uint32_t number1;
    fread(&number1, sizeof(number1), 1, file1);
    number1 = ntohl(number1);  // 네트워크 바이트 순서를 호스트 바이트 순서로 변환합니다.
    fclose(file1);

    // 두 번째 파일에서 숫자를 읽어옵니다.
    FILE *file2 = fopen(argv[2], "rb");
    if (!file2) {
        std::cerr << "두 번째 파일을 열 수 없습니다.\n";
        fclose(file1);  // 첫 번째 파일 닫기
        return 1;
    }

    uint32_t number2;
    fread(&number2, sizeof(number2), 1, file2);
    number2 = ntohl(number2);  // 네트워크 바이트 순서를 호스트 바이트 순서로 변환합니다.
    fclose(file2);

    // 두 숫자의 합을 계산합니다.
    uint32_t sum = number1 + number2;

    // 결과를 출력합니다.
    std::cout << number1 << "(0x" << std::hex << number1 << ") + "
              << std::dec << number2 << "(0x" << std::hex << number2 << ") = "
              << std::dec << sum << "(0x" << std::hex << sum << ")\n";

    return 0;
}


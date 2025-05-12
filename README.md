# Firesky

Firesky được phát triển bằng C++ (MSVC) và SDL3. 

# Mục tiêu trò chơi
- Người chơi điều khiển 1 máy bay với mục tiêu bắn hạ các máy bay địch, qua wave và đạt điểm số cao nhất
- Khi đạt mốc điểm nhất định, có thể nâng cấp vũ khí (súng, tên lửa) 
- Khi máu người chơi về 0, trò chơi kết thúc

# Các tính năng

- Người chơi liên tục bắn ra đạn và có thể bắn tên lửa với sát thương lớn
- Đường đạn bắn ra bởi máy bay địch tự bay về hướng người chơi

# Cách chơi
- Sử dụng các phím W/A/S/D để di chuyển
- Bấm phím F để phóng tên lửa

# Cách tải game

## Cách 1: Không bao gồm mã nguồn.

Tải game ở phần Release trên github, giải nén và chạy file FireSky.exe

## Cách 2: Bao gồm toàn bộ mã nguồn (dành cho những người muốn mod lại/thay đổi các tham số game).

**Lưu ý: Game được viết bằng MSVC nên không thể compile, build và chạy bằng GCC, Clang và các compiler khác**
- Clone repository : Chạy Terminal -> gõ lệnh "git clone https://github.com/Whittley-chan/FireSky.git" 
- Tải và cài đặt Visual Studio Build Tools (hoặc Visual Studio 2022)
    + Trong phần Visual Studio Installer, chọn cài đặt các thành phần: 
        "MSVC v143 - VS 2022 C++ x86/64 build tools"
        "C++ CMake tools for Windows"
        "Windows 11 SDK" (hoặc Windows 10 SDK nếu đang dùng Windows 10)
    + Cài đặt

- Sau khi cài đặt, vào Start -> x64 Native Tools Command Prompt for VS 2022
    + Dùng các lệnh: 
        cd [đuòng dẫn đến thư mục game vừa giải nén]
        mkdir bin
        cd bin
        cmake .. -G "NMake Makefiles"
        nmake
    + Sau khi make thành công, copy các file/folder sau vào /bin
        resources
        src/SDL3.dll
        src/SDL3_image.dll
        src/SDL3_ttf.dll

**Nếu dùng Visual Studio: chạy file FireSky.sln và build**

# Cấu trúc
**Mã nguồn: folder /src** 
**Hình ảnh, font chữ: folder /resources** 
**Thư viện SDL3: folder /SDL** 
**Header: folder /include** 


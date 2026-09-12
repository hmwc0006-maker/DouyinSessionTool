# DouyinSessionTool

Windows x64 CEF-based session token extractor for Douyin.

## Features

- Left: Built-in Chromium browser (opens Douyin web)
- Right: Session status panel (real-time refresh)
- Buttons: Re-login, Refresh, Clear session

## Build

GitHub Actions auto-builds. Or local:

```
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Tech Stack

- C++17, CEF 80, Windows API, GitHub Actions CI/CD

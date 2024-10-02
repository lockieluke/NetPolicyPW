# NetPolicyPW

> [!CAUTION]
> Disclaimer: This tool is for educational purposes only. I am not responsible for any misuse of this tool.

A tool to extract WiFi passwords from a chrome://net-export log file

## Build
```shell
git clone https://github.com/lockieluke/NetPolicyPW
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Usage

1. Visit [chrome://net-export](chrome://net-export)
2. In **OPTIONS** check **Include raw bytes (will include cookies and credentials)**
3. Click **Start Logging to Disk**
4. Open a new tab and visit [chrome://policy](chrome://policy)
5. Click **Reload policies**
6. Go back to [chrome://net-export](chrome://net-export) and click **Stop logging**
7. Run `./NetPolicyPW [full path to log file]`

Credit: [https://luphoria.com/netlog-policy-password-tool](https://luphoria.com/netlog-policy-password-tool)

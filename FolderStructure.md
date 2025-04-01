```sh
📦 spider-app/
├── 📂 backend/             # Python backend (WebSockets, flashing, API)
│   ├── 📂 src/
│   │   ├── flash_server.py  # WebSockets flashing logic
│   │   ├── api.py          # API server (if needed)
│   │   ├── utils.py        # Common utilities
│   ├── requirements.txt    # Python dependencies
│   ├── venv/               # Virtual environment (optional)
│   ├── README.md           
│
├── 📂 firmware/            # C++ (ESP32 firmware using PlatformIO)
│   ├── 📂 src/
│   │   ├── main.cpp        # Main ESP32 firmware logic
│   │   ├── motor_control.cpp # Motor control logic
│   │   ├── sensors.cpp     # Sensor reading logic
│   │   ├── config.h        # Configuration headers
│   ├── platformio.ini      # PlatformIO configuration
│   ├── README.md
│
├── 📂 frontend/            # TypeScript (React/Next.js UI)
│   ├── 📂 src/
│   │   ├── components/     # React components
│   │   ├── pages/          # Next.js pages (if using Next.js)
│   │   ├── utils/          # Helper functions
│   ├── package.json        # Dependencies
│   ├── tsconfig.json       # TypeScript config
│   ├── vite.config.ts      # Vite config (if using Vite)
│   ├── README.md
│
├── 📂 docs/                # Documentation
│   ├── architecture.md     # Project architecture
│   ├── setup.md            # Setup instructions
│
├── .gitignore              # Git ignore rules
├── LICENSE                 # Apache 2.0 License
├── README.md               # Main project README

```
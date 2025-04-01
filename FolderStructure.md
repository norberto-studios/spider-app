```sh
📦 spider-app/
├── 📂 backend/             # Python backend (WebSockets, flashing, API)
│   ├── 📂 src/
│   │   ├── server.py  # WebSockets flashing logic
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
├── 📂 frontend/            # Svelte 5 Application
│   ├── 📂 src/
│   │   ├── components/     # Svelte components
│   │   ├── routes/          # SvelteKit routes
│   │   ├── lib/            # Utility functions and libraries
│   ├── package.json        # Project dependencies and scripts
│   ├── svelte.config.js    # Svelte configuration
│   ├── tsconfig.json      # TypeScript configuration
│   ├── vite.config.ts     # Vite configuration (for build and dev server)
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
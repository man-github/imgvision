# imgvision  
High-performance C/C++ Image Classification + OCR Library  
Integrating **Darknet YOLO** object detection with **Tesseract OCR**, built for:

- Low-latency inference  
- Zero Python dependencies  
- Thread-safe API handles  
- .deb packaging for Linux distributions  
- Clean Autotools + Libtool build system  
- CI/CD via GitHub Actions  

---

## ⚡ Key Features

### ✔ High-performance C/C++ implementation  
Uses native Darknet + Tesseract APIs. No Python wrappers, no system() calls.

### ✔ Unified API  
One function call returns both:
- Object classifications (label + confidence)
- Extracted OCR text

### ✔ Thread-safe handles  
Each thread gets its own `ApiContext` (Tesseract + YOLO state).

### ✔ Autotools / Automake build system  
Standard Linux packaging workflow:

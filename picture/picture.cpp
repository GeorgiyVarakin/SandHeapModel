#include "picture.h"

Color::Color() {
    this->R = 0;
    this->B = 0;
    this->G = 0;
}

Color::Color(float r, float g, float b) {
    R = r;
    G = g;
    B = b;
}

sandPicture::sandPicture(int width, int height) {
    m_width = width;
    m_height = height;
    m_colors = new Color[width * height + 1];
}

Color sandPicture::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void sandPicture::SetColor(const Color &color, int x, int y) {
    m_colors[y * m_width + x].R = color.R;
    m_colors[y * m_width + x].G = color.G;
    m_colors[y * m_width + x].B = color.B;
}

void sandPicture::Export(const std::string& path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "ERROR OPENING FILE\n";
        return;
    }

    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

    unsigned char fileHeader[fileHeaderSize];

    // File type                                0-1
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size                                2-5
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (Not used)                    6-7
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 2 (Not used)                    8-9
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset                        10-13
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size                              0-3
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // sandPicture width                              4-7
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;
    // sandPicture height                             8-11
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;
    // Planes                                   12-13
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel (RGB)                     14-15
    informationHeader[14] = 24;
    informationHeader[15] = 0;
    // Compression (No compression)             16-19
    // sandPicture size (No compression)              20-23
    // X pixels per meter (Not specified)       24-27
    // Y pixels per meter (Not specified)       28-31
    // Total colors (Color palette not used)    32-35
    // Important colors (Generally ignored)     36-39
    for (int i = 16; i < informationHeaderSize; i++) {
        informationHeader[i] = 0;
    }

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char r = static_cast<unsigned char> (GetColor(x, y).R ); // * 255.0f
            unsigned char g = static_cast<unsigned char> (GetColor(x, y).G );
            unsigned char b = static_cast<unsigned char> (GetColor(x, y).B );

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }
    f.close();
}
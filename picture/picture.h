#include <iostream>
#include <vector>
#include <fstream>


struct Color {
    float R;
    float G;
    float B;

    Color();

    Color(float r, float g, float b);

    ~Color(){};

    static Color white() {
        return Color(255, 255, 255);
    }

    static Color green() {
        return Color(0, 255, 0);
    }

    static Color yellow() {
        return Color(255, 255, 0);
    }
    static Color violet() {
        return Color(255, 0, 255);
    }

    static Color black() {
        return Color(0, 0, 0);
    }

};

class sandPicture {
public:
    sandPicture(int width, int height);

    ~sandPicture() = default;

    Color GetColor(int x, int y) const;

    void SetColor(const Color &color, int x, int y);

    void Export(const std::string &path) const;

private:
    int m_width;
    int m_height;
    Color* m_colors;
};
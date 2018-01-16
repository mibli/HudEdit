#ifndef HUD_H
#define HUD_H

class Hud
{
public:
    static constexpr int xRes = 1920;
    static constexpr int yRes = 1080;

    static constexpr double xVar = 0.64;
    static constexpr double yVar = 0.64;

    static constexpr int MinSize = 0;
    static constexpr int MaxSize = 1280;

    enum CursorRelativePosition
    {
        Outside        = 0,
        Inside        = 1ul << 0,
        OverLeft    = 1ul << 1,
        OverRight    = 1ul << 2,
        OverTop        = 1ul << 3,
        OverBottom    = 1ul << 4
    };

    enum EditMode
    {
        Default        = 0,
        RectSelect    = 1
    };
};

#endif // HUD_H

#pragma once

namespace Core
{
    namespace Maths
    {
        class vec2
        {
            public:
                vec2();
                vec2(const float& x, const float& y);
                ~vec2();

                float x;
                float y;
        };
    }
}
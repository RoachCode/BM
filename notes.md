# markdown

switch (spriteColour)
        {
        case Default:
            pixels[i + 0] = rw;
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Inverted:
            if (rw <= 34 && gw <= 34 && bw <= 34)
            {
                pixels[i + 0] = rw; // assigns the value at r to the pixels object
                pixels[i + 1] = gw;
                pixels[i + 2] = bw;
            }
            else
            {
                pixels[i + 0] = 255 - rw; // assigns the value at r to the pixels object
                pixels[i + 1] = 255 - gw;
                pixels[i + 2] = 255 - bw;
            }
            pixels[i + 3] = aw;
            break;
        case Black:
            if (rw > 45 || gw > 45 || bw > 45)
            {
                aw = 0;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Transparent:
            if (aw > 250)
            {
                aw = 127;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Blue:
            if (rw + gw + bw > 255)
            {
                bw = 255;
            }
            else
            {
                bw = rw + gw + bw;
                rw = 0;
                gw = 0;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Dark:
            pixels[i + 0] = rw / 2; // assigns the value at r to the pixels object
            pixels[i + 1] = gw / 2;
            pixels[i + 2] = bw / 2;
            pixels[i + 3] = aw;
            break;
        default:
            pixels[i + 0] = rw;
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        }
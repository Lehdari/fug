#ifndef FUG_CONSTANTS_HPP
#define FUG_CONSTANTS_HPP


namespace fug {

    namespace WorldDir {
        const Vector3f up(0, 1.f, 0);
        const Vector3f down(0, -1.f, 0);
        const Vector3f left(-1.f, 0, 0);
        const Vector3f right(1.f, 0, 0);
    }

    namespace Input {
        enum Action {
            Up,
            Down,
            Left,
            Right,
            Shoot
        };
    }

    // Eventtien portteja vois määritellä tänne?
    //namespace Ports {
    //    namespace type {
    //        enum {
    //            port1,
    //            port2
    //        }
    //    }
    //}

}

#endif // FUG_CONSTANTS_HPP

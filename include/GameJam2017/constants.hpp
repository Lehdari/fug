#ifndef FUG_CONSTANTS_HPP
#define FUG_CONSTANTS_HPP


namespace fug {

    namespace WorldDir {
        const Eigen::Vector3f up(0, 1.f, 0);
        const Eigen::Vector3f down(0, -1.f, 0);
        const Eigen::Vector3f left(-1.f, 0, 0);
        const Eigen::Vector3f right(1.f, 0, 0);
    }

    namespace Input {
        enum Action {
            Up,
            Down,
            Left,
            Right,
            Fire
        }
    }

}

#endif // FUG_CONSTANTS_HPP

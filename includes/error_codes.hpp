//
// Created by Kateryna on 21.03.2024.
//

#ifndef INTEGRATE_PARALLEL_ERROR_CODES_HPP
#define INTEGRATE_PARALLEL_ERROR_CODES_HPP

enum ErrorCode {
    NO_ERROR = 0,
    WRONG_NUM_ARGS = 1,
    WRONG_METHOD_NUM = 2,
    ERROR_OPENING_FILE = 3,
    NOT_ENOUGH_DATA_IN_CONFIG = 5,
    MAX_ITER_EXCEEDED = 16
};

#endif //INTEGRATE_PARALLEL_ERROR_CODES_HPP
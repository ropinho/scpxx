//
// Created by pinho on 21/11/2019.
//

#ifndef ORLIB_SCPFILE_H
#define ORLIB_SCPFILE_H

#include "../InstanceFile.h"

class SCPFile : public InstanceFile {
public:
    /*
     * Default constructor
     */
    explicit SCPFile(std::string filename) : InstanceFile(filename) {
        if (!this->is_open()) {
            throw std::runtime_error("SCPFile not opened.");
        }
    }
};


#endif //ORLIB_SCPFILE_H

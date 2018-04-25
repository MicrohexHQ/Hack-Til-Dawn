//
// Created by Work on 4/26/2018.
//

#ifndef HACKATHON_IDEAS_H
#define HACKATHON_IDEAS_H

#include "generic.h"
using namespace generic;

namespace ideas {
    // @abi table ideas i64
    struct Idea {
        uuid                    id;
        string                  description;
        uint64_t                upvotes;
        uint64_t                flags;

        uuid primary_key() const { return id; }
        EOSLIB_SERIALIZE( Idea, (id)(description)(upvotes)(flags) )
    };

    // @abi action
    struct IdeaAction {
        uuid                    keyid;
        uuid                    ideaid;

        uuid primary_key() const { return keyid; }
        EOSLIB_SERIALIZE( IdeaAction, (keyid)(ideaid) )
    };
}

#endif //HACKATHON_IDEAS_H

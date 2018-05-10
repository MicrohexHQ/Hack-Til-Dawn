#ifndef HACKATHON_GENERIC_H
#define HACKATHON_GENERIC_H

namespace generic {
    static constexpr uint64_t code = N(hackathon);
    
    // TYPEDEFS
    typedef uint64_t    uuid;
    typedef uint64_t    project_vote;
    typedef uint8_t     boolean;

    // REUSABLE STRUCTS
    struct Link {
        string name;
        string url;

        EOSLIB_SERIALIZE( Link, (name)(url) )
    };

    // @abi table usernames i64
    // @abi table teamnames i64
    // @abi table projnames i64
    struct NameToKey {
        uuid                    nameid;
        uuid                    keyid;

        uuid primary_key() const { return nameid; }
        EOSLIB_SERIALIZE( NameToKey, (nameid)(keyid) )
    };

    // @abi table memberteams i64
    struct MemberVector {
        uuid                    keyid;
        vector<uuid>            teamids;

        uuid primary_key() const { return keyid; }
        EOSLIB_SERIALIZE( MemberVector, (keyid)(teamids) )
    };

    // @abi table settings i64
    struct Settings {
        uint64_t                stopped;
        uint64_t                votingEnabled;
        uint64_t                projectsEnabled;
        account_name            appKey;
        checksum256             proof;

        uuid primary_key() const { return 0; }
        EOSLIB_SERIALIZE( Settings, (stopped)(votingEnabled)(projectsEnabled)(appKey)(proof) )
    };

    // @abi table shares i64
    struct Share {
        uuid                   userid;
        uint64_t               count;

        uuid primary_key() const { return userid; }
        EOSLIB_SERIALIZE( Share, (userid)(count) )
    };


    // HELPERS
    inline static uint64_t murmur( const string& strkey ){
        return std::hash<string>{}(strkey);
    }

    /***
     * Turns an integer into a vector of ints ( ie 1024 == [1,0,2,4] )
     * @param i
     * @return
     */
    const vector<uint64_t> intToVector( uint64_t i ){
        vector<uint64_t> v;
        while(i > 0){
            v.push_back(i%10);
            i/=10;
        }
        reverse(v.begin(), v.end());
        return v;
    }

    /***
     * Concatenates two integers together ( ie 1024+1024 = 10241024 [NOT] 2048 )
     * @param a
     * @param b
     * @return
     */
    const uint64_t concatInts( const uint64_t& a, const uint64_t& b ){
        vector<uint64_t> va = intToVector(a);
        vector<uint64_t> vb = intToVector(b);
        va.insert(va.end(), vb.begin(), vb.end());
        reverse(va.begin(), va.end());

        int index = 1;
        uint64_t res = 0;
        for ( auto i : va ){
            res += i*index;
            index*=10;
        }
        return res;
    }

    template <typename T>
    T clamp( T a, T min, T max ){
        return a > max ? max
               : a < min ? min
               : a;
    }

    template <typename T>
    T add( T a, T b ){
        return a+b <= std::numeric_limits<T>::max()
             ? a+b  : std::numeric_limits<T>::max();
    }

    template <typename T>
    T sub( T a, T b ){
        return a-b >= std::numeric_limits<T>::min()
             ? a-b  : std::numeric_limits<T>::min();
    }

    template <typename T>
    T mul( T a, T b ){
        return a*b <= std::numeric_limits<T>::max()
             ? a*b  : std::numeric_limits<T>::max();
    }
}

#endif //HACKATHON_GENERIC_H

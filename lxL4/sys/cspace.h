#pragma once

#include "cap.h"

/*enum well_known_caps {
	WKCAP_SELF = 0,
	WKCAP_NEXT,
	WKCAP_CALLER,
	WKCAP_RESERVED,
	MAX_WK_CAPS,
};

#define MAX_CAPS 1024
#define MAX_PUB_CAPS (MAX_CAPS - MAX_WK_CAPS)
#define CIDMASK (MAX_CAPS - 1)
#define N_WKCIDMASK (~(MAX_WK_CAPS - 1) & CIDMASK)

typedef struct cspublic_t {
	cap_t caps[MAX_CAPS];
} cspublic_t;

typedef struct cspace {
	cap_t wk_caps[MAX_WK_CAPS];
	cspublic_t *cspub;
} cspace_t;

#define CS_GET_CAP(cs, id) (((id) & N_WKCIDMASK) == 0 ? \
		&((cs)->wk_caps[(id)]) : CSPUB_GET_CAP((cs)->cspub, id))
#define CSPUB_GET_CAP(cspub, id) (&((cspub)->caps[(id)]))
*/

#include "cid.h"

typedef struct cspace {
	cap_t caps[MAX_CAPS];
} cspace_t;

/* luna_fsm.h */
#ifndef LUNA_FSM_H
#define LUNA_FSM_H

#include <stdint.h>

#ifndef LUNA_FSM_ASSERT
#define LUNA_FSM_ASSERT(expr) ((void)0)
#endif

#define RET_HANDLED		(uint32_t)(0)
#define RET_IGNORED		(uint32_t)(1)
#define RET_TRANSFER		(uint32_t)(2)

#define HAND()		RET_HANDLED
#define IGNO()		RET_IGNORED
#define TRAN(t) \
			(((struct luna_fsm *)me)->handler = (luna_fsm_handler_t)(t), RET_TRANSFER)

struct luna_fsm_evt {
	uint32_t sig;
};

struct luna_fsm;

typedef uint32_t (*luna_fsm_handler_t)(struct luna_fsm *fsm, const struct luna_fsm_evt *evt);

// Based on the current status and the received events, perform actions according to predefined rules and switch the status.
struct luna_fsm {
	luna_fsm_handler_t handler;
};

enum {
	EMPTY_SIG = 0,
	ENTER_SIG,
	EXIT_SIG,
	INIT_SIG,
	USER_SIG,
};

void luna_fsm_ctor(struct luna_fsm *me, luna_fsm_handler_t handler);
void luna_fsm_init(struct luna_fsm *me, struct luna_fsm_evt const *evt);
void luna_fsm_dispatch(struct luna_fsm *me, const struct luna_fsm_evt *evt);

#endif

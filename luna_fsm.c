/* luna_fsm.c */
#include "luna_fsm.h"

const struct luna_evt luna_internal_sig[] = {
	{.sig = SIG_EMPTY},
	{.sig = SIG_ENTER},
	{.sig = SIG_EXIT},
	{.sig = SIG_INIT},
	{.sig = SIG_INTERRUPT},
};

void luna_fsm_init(struct luna_fsm *me)
{
	LUNA_FSM_ASSERT(me);
	LUNA_FSM_ASSERT(me->handler);

	(void)(*me->handler)(me, &luna_internal_sig[SIG_INIT]);
	(void)(*me->handler)(me, &luna_internal_sig[SIG_ENTER]);
}

void luna_fsm_dispatch(struct luna_fsm *me, const struct luna_evt *evt)
{
	LUNA_FSM_ASSERT(me);
	LUNA_FSM_ASSERT(evt);

	luna_fsm_handler_t handler = me->handler;
	LUNA_FSM_ASSERT(handler != NULL);

	uint32_t rt = handler(me, evt);
	if (TRANSFER == rt) {
		(void)handler(me, &luna_internal_sig[SIG_EXIT]);
		(void)(*me->handler)(me, &luna_internal_sig[SIG_ENTER]);
	}
}

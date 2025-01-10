/** @addtogroup tik_tak
 * @{
 */
/** @file
 */

#include <types/common.h>
#include <io/console.h>
#include <async.h>
#include <stdbool.h>

typedef struct {
	sysarg_t ws_row;
	sysarg_t ws_col;
} winsize_t;

extern console_ctrl_t *console;
extern winsize_t winsize;

extern void moveto(sysarg_t r, sysarg_t c);
extern void clear_screen(void);
extern void scr_clear(void);
extern void scr_end(void);
extern void scr_init(void);
extern void scr_msg(char *, bool);




/** @}
 */

set helpmsg "Game of Life

Keys:
<space>\ttoggle
<q>\tquit
<c>\tclear
<r>\trandom
<F1>\thelp"

package require Tk
bind . <q> {exit}

frame .f
canvas .f.c -background gray
button .f.bt -text Stop -command toggle
button .f.bs -text Step   -command {set ::interrupt 1; process_bricks; draw_bricks}
button .f.bc -text Clear  -command clear
button .f.br -text Random -command random
button .f.bq -text Quit   -command exit

grid .f -column 0 -row 0
grid .f.c -column 0 -row 0 -columnspan 3
grid .f.bt -column 0 -row 1
grid .f.bs -column 1 -row 1
grid .f.bc -column 2 -row 1
grid .f.br -column 0 -row 2
grid .f.bq -column 1 -row 2

set ::heldbutton 0

bind . <space> {toggle}
bind . <c> clear
bind . <r> random
bind . <F1> {set ::interrupt 1; help}
bind .f.c <ButtonPress>   {set ::heldbutton %b; handle_mouse %b %x %y}
bind .f.c <ButtonRelease> {set ::heldbutton 0}
bind .f.c <Motion> {if {$::heldbutton} {handle_mouse $::heldbutton %x %y}}

set timestep 50; # ms
set BWIDTH  10
set BHEIGHT 10
set BRICK_NX [expr {[winfo reqwidth  .f.c] / $BWIDTH}]
set BRICK_NY [expr {[winfo reqheight .f.c] / $BHEIGHT}]
set GAP 0

proc init_bricks {value} {
	set bricks {}
	for {set j 0} {$j < $::BRICK_NY} {incr j} {
		lset bricks $j {}
		for {set i 0} {$i < $::BRICK_NX} {incr i} {
			lset bricks $j $i [expr $value]
		}
	}
	return $bricks
}

proc draw_bricks_init {} {
	for {set j 0} {$j < $::BRICK_NY} {incr j} {
		for {set i 0} {$i < $::BRICK_NX} {incr i} {
			set x0 [expr {$::BWIDTH * $i}]
			set y0 [expr {$::BHEIGHT * $j}]
			set b [lindex $::bricks $j $i]
			set color [expr {$b ? "black" : "white"}]

			lset ::rect_ids $j $i [.f.c create rectangle \
				$x0 $y0 [expr {$x0 + $::BWIDTH - $::GAP}] [expr {$y0 + $::BHEIGHT - $::GAP}] \
				-fill $color -outline grey]
		}
	}
}

proc draw_bricks {} {
	for {set j 0} {$j < $::BRICK_NY} {incr j} {
		for {set i 0} {$i < $::BRICK_NX} {incr i} {
			set x0 [expr {$::BWIDTH * $i}]
			set y0 [expr {$::BHEIGHT * $j}]
			set b [lindex $::bricks $j $i]
			set color [expr {$b ? "black" : "white"}]

			.f.c itemconfigure [lindex $::rect_ids $j $i] -fill $color
		}
	}
}

proc process_bricks {} {
	for {set j 0} {$j < $::BRICK_NY} {incr j} {
		for {set i 0} {$i < $::BRICK_NX} {incr i} {
			set neighbours 0
			set b [lindex $::bricks $j $i]
			
			foreach dx {-1 0 1} {
				foreach dy {-1 0 1} {
					set ii [expr {$i + $dx}]
					set jj [expr {$j + $dy}]
					if {$jj >= $::BRICK_NY || $jj < 0 || $ii >= $::BRICK_NX || $ii < 0 || (($dx==0)&&($dy==0)) } {
						continue
					}
					incr neighbours [lindex $::bricks $jj $ii]
				}
			}

			if {$neighbours < 2 || $neighbours > 3} {
				lset ::newbricks $j $i 0
			} elseif {$b && $neighbours == 2} {
				lset ::newbricks $j $i 1
			} elseif {$neighbours == 3} {
				lset ::newbricks $j $i 1
			} else {
				lset ::newbricks $j $i 0
			}
		}
	}

	set ::bricks $::newbricks
}

set interrupt 0
proc loop {} {
	if {$::interrupt} {return}
	process_bricks
	draw_bricks
	after $::timestep loop
}

proc toggle {} {
	if {$::interrupt} {
		.f.bt configure -text Stop
		set ::interrupt 0
		loop
	} else {
		.f.bt configure -text Start
		set ::interrupt 1
	}
}

proc help {} {
	tk_messageBox -message $::helpmsg
}

proc handle_mouse {b x y} {
	# button 1 sets on, button 3 sets off. therefore map 1->1, 3->0, ignore 2.
	if {$b == 2} return
	set b [expr {(3-$b)/2}]

	set col [expr {$x / $::BWIDTH}]
	set row [expr {$y / $::BHEIGHT}]
	# check in range?

	lset ::bricks $row $col $b
	draw_bricks
}

proc clear {} {
	set ::bricks [init_bricks 0]
	draw_bricks
}

proc random {} {
	set ::bricks [init_bricks round(rand())]
	draw_bricks
}

set bricks [init_bricks round(rand())]
set newbricks [init_bricks 0]
set rect_ids [init_bricks 0]
draw_bricks_init

loop

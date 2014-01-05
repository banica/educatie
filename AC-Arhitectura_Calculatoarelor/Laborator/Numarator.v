`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:42:01 10/17/2006 
// Design Name: 
// Module Name:    Numarator 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Numarator(CLOCK, led);
    input CLOCK;
	 output [0:7] led;
    reg [0:31] r;
	 reg [0:7] x;

initial
    begin
	 x=0;
    end
	 
always @(posedge CLOCK)
    begin
	 r=r+1;
	 if (r==50000000)
	    begin
			x=x+1;
		 end
	 end

assign led=x;
	 
endmodule

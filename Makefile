all: compile

compile:
	rebar compile

deps:
	rebar get-deps

run:
	rebar shell

clean:
	rebar clean


#include "menu.hpp"

/// WARNING:
/// HELLO THERE FUTURE ME, THIS IS NOT PROPERLY DONE LMAO, PLEASE STOP BEING LAZY AND DO IT THE RIGHT WAY.
/// FUCK YOU

void menu::menu_t::main_form( const static std::string_view string, const static math::vec2_t& pos, const static math::vec2_t& size, const static col_t& color, const static std::uint8_t fade_time ) {
	try {
		if ( !this->initialized )
			this->initialized = !this->initialized;
		this->_size = size;																									/// So we can use this in the entire menu framework
		this->_pos = pos;

		ctx::csgo.engine->get_screen_size( reinterpret_cast< int& >( this->screen_size.x ), reinterpret_cast< int& >( this->screen_size.y ) );		/// Gather client's monitor resolution

		/*
			Fade in/out calcs here
		*/

		render::rect( { pos.x, pos.y }, { size.x, size.y }, col_t::palette_t::black( ) );									/// Black outline
		render::rect( { pos.x + 1, pos.y + 1 }, { size.x - 2, size.y - 2 }, col_t::palette_t::white( 35u ) );				/// White outline

		render::rect_filled( { pos.x, pos.y }, { size.x, size.y }, col_t::palette_t::black( 185u ) );

		render::rect( { pos.x + 5, pos.y + 5 }, { size.x - 10, size.y - 10 }, col_t::palette_t::white( 35u ) );				/// White outline

		render::rect_filled( { pos.x + 5, pos.y + 5 }, { size.x - 10, size.y - 10 }, col_t::palette_t::black( 185u ) );
		render::rect_filled( { pos.x + 20, pos.y + 45 }, { size.x - 40, size.y - 65 }, col_t( 20, 20, 20 ) );

		render::rect( { pos.x + 20, pos.y + 45 }, { size.x - 40, size.y - 65 }, col_t::palette_t::black( ) );				/// Black outline
		render::rect( { pos.x + 21, pos.y + 46 }, { size.x - 42, size.y - 67 }, col_t::palette_t::white( 10u ) );			/// White outline

		render::text( render::fonts::m_main, { pos.x + size.x - render::text_size( render::fonts::m_main, string ).x - 19, pos.y + size.y - 18 }, col_t::palette_t::white( 50u ), { }, string );

		for ( std::uint8_t i = 0; i < menu::tabs.size( ); i++ ) {
			render::text( render::fonts::m_main, { pos.x + 30 + ( 61 * i ), pos.y + 20 }, col_t::palette_t::white( 100u ), { render::fonts::FONT_CENTER_X }, menu::tabs.at( i ) );
			render::rect_filled( { pos.x + 20 + ( 61 * i ), pos.y + 35 }, { 58, 2 }, col_t( 100, 100, 100, 30 ) );
			render::rect_filled( { pos.x + 20 + ( 61 * i ), pos.y + 37 }, { 58, 2 }, col_t::palette_t::black( 145u ) );
		}
	}
	catch ( std::runtime_error& err ) {
		LOG( err.what( ) );
		std::runtime_error( err.what( ) );
	}
}

void menu::menu_t::handle_dragging( ) {
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	try {
		if ( ( this->_pos.x + this->_size.x ) > this->screen_size.x || ( this->_pos.y + this->_size.y ) > this->screen_size.y
				|| ( this->_pos.x ) < this->screen_size.x || ( this->_pos.y ) < this->screen_size.y )
			return;
	}
	catch ( std::runtime_error& err ) {
		LOG( err.what( ) );
		std::runtime_error( err.what( ) );
	}
}

void menu::menu_t::config_tabs( const std::vector<std::string> tabs_amount ) {
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	try {
		for ( std::uint8_t i = 0; i < tabs_amount.size( ); i++ ) {
			menu::tabs.at( i ).assign( tabs_amount.at( i ) );
		}
	}
	catch ( std::runtime_error& err ) {
		LOG( err.what( ) );
		std::runtime_error( err.what( ) );
	}
}

void menu::menu_t::groupbox( const std::string_view& string ) {
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	try {
		render::rect( { this->_pos.x + 21 + 19, this->_pos.y + 46 + 21 }, { 211, 146 }, col_t::palette_t::black( ) );
		render::rect( { this->_pos.x + 21 + 19, this->_pos.y + 46 + 21 }, { 210, 145 }, col_t::palette_t::white( 10u ) );

		render::rect( { this->_pos.x + 21 + 28, this->_pos.y + 46 + 21 }, { render::text_size( render::fonts::m_main, string ).x + 3, 1 }, col_t( 20, 20, 20 ) );
		render::text( render::fonts::m_main, { this->_pos.x + 21 + 30, this->_pos.y + 46 + 15 }, col_t::palette_t::white( 200u ), { }, string );
	}
	catch ( std::runtime_error& err ) {
		LOG( err.what( ) );
		std::runtime_error( err.what( ) );
	}
}

void menu::menu_t::checkbox( const std::string_view& string, bool state, bool enabled = false ) {
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	try {
		if ( input::get_key_info( MOUSEEVENTF_LEFTDOWN ).is_pressed( ) )
			state = !state;

		render::rect( { this->_pos.x + 55, this->_pos.y + 83 }, { 8, 8 }, col_t::palette_t::dark_grey( ) ); // outline
		render::rect_filled( { this->_pos.x + 56, this->_pos.y + 84 }, { 6, 6 }, state ? col_t::palette_t::red( ) : col_t::palette_t::white( 10u ) ); // actual color

		render::text( render::fonts::m_main, { this->_pos.x + 75, this->_pos.y + 81 }, col_t::palette_t::white( 200u ), { }, string );
	}
	catch ( std::runtime_error& err ) {
		LOG( err.what( ) );
		std::runtime_error( err.what( ) );
	}
}

template <typename t>
void menu::menu_t::slider( t style, const std::string_view& string, t config, t value ) {
	/*if ( ( style != ) float || int )
		throw std::runtime_error( "slider can only be either: float; int" );

	render::rect_filled( { this->_pos.x, this->_pos.y }, { 150, 8 }, col_t::palette_t::grey( ) );													/// CHANGE TO GRADIENT
	render::rect( { this->_pos.x, this->_pos.y }, { 150, 8 }, col_t::palette_t::black( ) );															/// OUTLINE
	
	render::rect_filled( { this->_pos.x, this->_pos.y }, { static_cast<t>( this->slider_value ), 8 }, col_t::palette_t::grey( ) );					/// ACTUAL SLIDER

	render::text( render::fonts::m_main, { static_cast< t >( this->slider_value.x, static_cast< t >( this->slider_value.y + 7 }, col_t::palette_t::white( 200u ), { }, 
		{ [[ static_cast< t >( this->slider_value ) + string ]] } );	/// TEXT UNDER SLIDER

	render::text( render::fonts::m_main, { static_cast< t >( this->slider_value.x + 160,  static_cast< t >( this->slider_value.y / 2 }, col_t::palette_t::white( 200u ), { }, "+" ); {
		static_cast< t >( this->slider_value )++;
	}
	render::text( render::fonts::m_main, { static_cast< t >( this->slider_value.x - 10,  static_cast< t >( this->slider_value.y / 2 }, col_t::palette_t::white( 200u ), { }, "-" ); {
		static_cast< t >( this->slider_value )--;
	}
	
		REMINDER: ALL THE CODE ABOVE IS TOTAL PSEUDO CODE, IT WILL NOT WORK!
	*/
}

void menu::menu_t::tooltip( const std::string_view& string ) {
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	/*if mouse hovered, show tooltip for latest added control, maybe create a vector (?)*/

	if ( string.empty( ) )
		return;
		
	render::line( { this->_pos.x + 20, this->_pos.y + this->_size.y - 13 }, { this->_pos.x + 28, this->_pos.y + this->_size.y - 13 }, col_t::palette_t::white( 50u ) );
	render::line( { this->_pos.x + 25, this->_pos.y + this->_size.y - 16 }, { this->_pos.x + 28, this->_pos.y + this->_size.y - 13 }, col_t::palette_t::white( 50u ) );
	render::line( { this->_pos.x + 25, this->_pos.y + this->_size.y - 10 }, { this->_pos.x + 28, this->_pos.y + this->_size.y - 13 }, col_t::palette_t::white( 50u ) );

	render::text( render::fonts::m_main, { this->_pos.x + 33, this->_pos.y + this->_size.y - 18 }, col_t::palette_t::white( 50u ), { }, string );
}

void menu::menu_t::notification( const std::string_view& string, uint8_t type, uint8_t time ) { /// MAX TIME IS 255 (in seconds)
	if ( !this->initialized )
		throw std::runtime_error( "menu hasn't been initialized yet!" );

	uint8_t _alpha = 255;

	/*
		Use tickcount or framerate to do b1g math and wait -> time

		game->global_vars( ).tickcount + (time * 1000);
	*/

	try {
		render::rect_filled( { 5, 116 }, { 258, 78 }, col_t( 20, 20, 20, _alpha ) );

		render::rect( { 4, 115 }, { 260, 80 }, col_t::palette_t::black( _alpha ) );		/// OUTLINE
		render::rect( { 5, 116 }, { 258, 78 }, col_t::palette_t::white( 35u ) );		/// OUTLINE

		render::text( render::fonts::m_main, { 100, 149 }, col_t::palette_t::white( 50u ), { }, string );

		switch ( type ) {
			case menu::notification_type_e::error:
				render::rect_filled( { 0, 115 }, { 3, 80 }, col_t::palette_t::red( _alpha ) );
				render::rect_filled( { 3, 152 }, { 1, 4 }, col_t::palette_t::red( _alpha ) );
				break;
			case menu::notification_type_e::info:
				render::rect_filled( { 0, 115 }, { 3, 80 }, col_t::palette_t::light_blue( _alpha ) );
				render::rect_filled( { 3, 152 }, { 1, 4 }, col_t::palette_t::light_blue( _alpha ) );
				break;
			case menu::notification_type_e::warning:
				render::rect_filled( { 0, 115 }, { 3, 80 }, col_t::palette_t::roasted_yellow( _alpha ) );
				render::rect_filled( { 3, 152 }, { 1, 4 }, col_t::palette_t::roasted_yellow( _alpha ) );
				break;
		}
	} catch ( std::exception& error ) {
		LOG( error.what( ) );
		std::runtime_error( error.what( ) );
	}
}

void menu::cursor_t::paint_cursor( ) { 
	
}
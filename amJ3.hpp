#pragma once

#include "../csgo.hpp"

namespace menu {
	inline bool toggled = true;
	inline static std::vector<std::string> tabs( 8 );

	struct menu_t {
		void main_form( const static std::string_view, const static math::vec2_t&, const static math::vec2_t&, const static col_t&, const static std::uint8_t );
		void config_tabs( const std::vector<std::string> );

		void groupbox( const std::string_view& );
		void checkbox( const std::string_view&, bool, bool );
		void tooltip( const std::string_view& );

		void notification( const std::string_view&, uint8_t, uint8_t );

		template<typename t>
		void slider( t, const std::string_view&, t, t );

		void handle_dragging( );

	private:
		bool initialized = false;
		math::vec2_t& _size = math::vec2_t( 0, 0 ), &_pos = math::vec2_t( 0, 0 );
		static math::vec2_t screen_size;
	};

	struct cursor_t {
		POINT cursor_pos;
		void paint_cursor( );
	};
	void init( );

	inline menu::menu_t* add = new menu::menu_t( );
	inline menu::cursor_t* cursor = new menu::cursor_t( );

	enum notification_type_e : uint8_t {
		error, warning, info
	};
}
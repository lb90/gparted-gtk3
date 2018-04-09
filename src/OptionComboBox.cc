/* Copyright (C) 2018 Luca Bacci
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "ComboBox.h"

#include <glibmm/ustring.h>

namespace GParted
{

OptionComboBox::OptionComboBox()
{
	m_model = Gtk::ListStore::create(m_columns);
	set_model( m_model );

	pack_start( m_cellrenderer );
	add_attribute( m_cellrenderer, "text",      m_columns.m_col_text );
	add_attribute( m_cellrenderer, "sensitive", m_columns.m_col_sensitive );
}

OptionComboBox::~OptionComboBox()
{
}

Glib::ustring OptionComboBox::get_active_text()
{
	Glib::ustring text;

	Gtk::TreeModel::const_iterator iter = get_active();
	if ( iter )
	{
		Gtk::TreeModel::Row row = *iter;
		text = row [ m_columns.m_col_text ];
	}
	
	return text;
}

void OptionComboBox::append(const Glib::ustring& text, bool sensitive)
{
	Gtk::TreeModel::Row row = *( m_model ->append() );

	row [ m_columns.m_col_text ] = text;
	row [ m_columns.m_col_sensitive ] = sensitive;
}

std::vector<OptionComboBox::Row> OptionComboBox::items()
{
	typedef Gtk::TreeModel::Children type_children;

	std::vector< Row > rows;	
	type_children children = m_model->children();
	
	for (type_children::iterator it = children.begin();
	     iter != children.end(); ++it)
	{
		/*TODO requires c++11 */
		rows.emplace_back(this, it);
	}
	
	/*TODO only works for c++11 thanks to move semantics if Row is not copyable */
	return rows;
}

void OptionComboBox::clear()
{
	m_model.clear();
}

OptionComboBox::Row::Row(OptionComboBox & parent, Gtk::TreeModel::iterator iter)
 : m_iter(iter),
   m_parent(parent)
{
}

OptionComboBox::Row::~Row()
{
}

Glib::ustring OptionComboBox::Row::get_text()
{
	return (*iter)[ parent.m_columns.m_col_text ];
}

void OptionComboBox::Row::set_text(const Glib::ustring& text)
{
	(*iter)[ parent.m_columns.m_col_text ] = text;
}

bool OptionComboBox::Row::get_sensitive()
{
	return (*iter)[ parent.m_columns.m_col_sensitive ];
}

void OptionComboBox::Row::set_sensitive(bool sensitive)
{
	(*iter)[ parent.m_columns.m_col_sensitive ] = sensitive;
}

}//GParted

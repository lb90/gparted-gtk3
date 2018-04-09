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


#ifndef GPARTED_OPTIONCOMBOBOX_H
#define GPARTED_OPTIONCOMBOBOX_H

#include <vector>

/*TODO review gtkmm includes */
#include <glibmm/ustring.h>
#include "gtkmm/combobox.h"
#include "gtkmm/treemodel.h"
#include "gtkmm/liststore.h"

namespace GParted
{

class OptionComboBox
 : public Gtk::ComboBox
{
public:
	class Row
	{
	public:
		Row ( OptionComboBox & parent, Gtk::TreeModel::iterator iter);
		~Row( );

		void set_text( const Glib::ustring & text );
		void set_sensitive( bool sensitive );

	private:
		/*TODO: what about implementing copy?
		        in that case we should not have a reference to parent,
		        we should really use a pointer */
		Row( const Row & );
		Row & operator=( const Row & );
	
		Gtk::TreeModel::iterator m_iter;
		OptionComboBox& m_parent;
	};

	OptionComboBox();
	~OptionComboBox();

	void append(const Glib::ustring & text, bool sensitive = true);
	std::vector< Row > items();
	void clear();
	
	Glib::ustring get_active_text() const;

private:
	OptionComboBox( const OptionComboBox & src );              // Not implemented copy constructor
	OptionComboBox & operator=( const OptionComboBox & rhs );  // Not implemented copy assignment operator
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns() { add(m_col_text); add(m_col_sensitive); }

		Gtk::TreeModelColumn<Glib::ustring> m_col_text;
		Gtk::TreeModelColumn<bool> m_col_sensitive;
	private:
		ModelColumns( const ModelColumns& );
		ModelColumns & operator=( const ModelColumns & );
	};

	ModelColumns                   m_columns;
	Glib::RefPtr<Gtk::ListStore>   m_model;
	Gtk::CellRendererText          m_cellrenderer;
};

}//GParted

#endif /* GPARTED_COMBOBOX_H */

#pragma once


// forward
class EditorBase;
namespace Gtk {
	class Frame;
}


//-------------------------------------------
// E_EditorTool
//
// Types of editor tools that can be created
//
enum class E_EditorTool
{
	SceneViewport,
	Outliner,

	Invalid
};


//-------------------------------------------
// I_EditorTool
//
// Interface for a tool that can be created for a given editor
//
class I_EditorTool
{
public:
	virtual ~I_EditorTool() = default;

	virtual void Init(EditorBase* const editor, Gtk::Frame* const parent) = 0;
	virtual void OnDeinit() {} // called before unattaching the frames child

	virtual bool IsToolbarTopPref() const { return true; }
};


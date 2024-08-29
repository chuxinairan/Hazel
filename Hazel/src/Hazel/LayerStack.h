#pragma once
#include "Hazel/core.h"
#include "Layer.h"

#include <vector>

namespace Hazel
{
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		virtual ~LayerStack();
		
		void PushLayer(Layer* layer);
		void PushOverlar(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlar(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}

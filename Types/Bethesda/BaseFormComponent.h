#pragma once

class BaseFormComponent {
	virtual void InitializeDataComponent();
	virtual void ClearDataComponent();
	virtual void CopyComponent(BaseFormComponent*);
	virtual bool CompareComponent(BaseFormComponent*);
};

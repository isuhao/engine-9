#ifndef Core_SoundView_h
#define Core_SoundView_h

class SoundView
{
public:
    /**
     * Default constructor that creates a new instance of a Controller.
     */
    SoundView();
    
    /**
     * Initializes the SoundView.
     */
    void Initialize();
    
    /**
     * Updates the SoundView.
     */
    void Update();
    
private:
    // Private constructors to disallow access.
    SoundView(SoundView const &other);
    SoundView operator=(SoundView other);
};

#endif

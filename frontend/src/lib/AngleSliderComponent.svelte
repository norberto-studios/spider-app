<script>
    // Props for the component
    export let value = 90; // Default value
    export let min = 0;
    export let max = 180;
    export let step = 1;
    export let label = "Angle";
    export let title = "Servo ";
    export let showMarkers = true;
    export let sliderId = 0;

    // Create a unique ID for this component instance
    // const sliderId = `angle-slider-${Math.random().toString(36).substring(2, 9)}`;

    // Event handler for input changes
    function handleInput(event) {
        const newValue = Number(event.target.value);
        // Update the value and dispatch an event
        value = newValue;
        // Create and dispatch a custom event
        const customEvent = new CustomEvent('change', {
            detail: { value: newValue }
        });
        event.target.dispatchEvent(customEvent);
    }
</script>

<div class="mt-6">
    <h4>{title}</h4>
    <label for={sliderId} class="block text-sm font-medium text-gray-700 mb-1">
        {label}: {value}°
    </label>
    <input
        id={sliderId}
        type="range"
        min={min}
        max={max}
        step={step}
        class="w-full h-2 bg-gray-300 rounded-lg appearance-none cursor-pointer"
        {value}
        on:input={handleInput}
        on:change
    />
    {#if showMarkers}
        <div class="flex justify-between w-full text-xs text-gray-500 mt-1">
            <span>{min}°</span>
            {#if min < max}
                <span>{Math.floor((min + max) / 2)}°</span>
            {/if}
            <span>{max}°</span>
        </div>
    {/if}
</div>
